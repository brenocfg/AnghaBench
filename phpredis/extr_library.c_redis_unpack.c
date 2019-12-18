#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  size_t uint32_t ;
struct TYPE_4__ {int compression; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  E2BIG ; 
#define  REDIS_COMPRESSION_LZF 129 
#define  REDIS_COMPRESSION_ZSTD 128 
 size_t ZSTD_decompress (char*,size_t,char const*,int) ; 
 size_t ZSTD_getFrameContentSize (char const*,int) ; 
 int /*<<< orphan*/  ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,size_t) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 int /*<<< orphan*/  errno ; 
 size_t lzf_decompress (char const*,int,char*,int) ; 
 int redis_unserialize (TYPE_1__*,char const*,int,int /*<<< orphan*/ *) ; 

int
redis_unpack(RedisSock *redis_sock, const char *val, int val_len, zval *z_ret)
{
    switch (redis_sock->compression) {
        case REDIS_COMPRESSION_LZF:
#ifdef HAVE_REDIS_LZF
            {
                char *data;
                int i;
                uint32_t res;

                errno = E2BIG;
                /* start from two-times bigger buffer and
                 * increase it exponentially  if needed */
                for (i = 2; errno == E2BIG; i *= 2) {
                    data = emalloc(i * val_len);
                    if ((res = lzf_decompress(val, val_len, data, i * val_len)) == 0) {
                        /* errno != E2BIG will brake for loop */
                        efree(data);
                        continue;
                    } else if (redis_unserialize(redis_sock, data, res, z_ret) == 0) {
                        ZVAL_STRINGL(z_ret, data, res);
                    }
                    efree(data);
                    return 1;
                }
            }
#endif
            break;
        case REDIS_COMPRESSION_ZSTD:
#ifdef HAVE_REDIS_ZSTD
            {
                char *data;
                size_t len;

                len = ZSTD_getFrameContentSize(val, val_len);
                if (len >= 0) {
                    data = emalloc(len);
                    len = ZSTD_decompress(data, len, val, val_len);
                    if (ZSTD_isError(len)) {
                        efree(data);
                        break;
                    } else if (redis_unserialize(redis_sock, data, len, z_ret) == 0) {
                        ZVAL_STRINGL(z_ret, data, len);
                    }
                    efree(data);
                    return 1;
                }
            }
#endif
            break;
    }
    return redis_unserialize(redis_sock, val, val_len, z_ret);
}