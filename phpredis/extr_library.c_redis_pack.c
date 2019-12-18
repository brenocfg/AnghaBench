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
struct TYPE_4__ {int compression; int compression_level; } ;
typedef  TYPE_1__ RedisSock ;

/* Variables and functions */
 int /*<<< orphan*/  LZF_MARGIN ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  REDIS_COMPRESSION_LZF 129 
#define  REDIS_COMPRESSION_ZSTD 128 
 int /*<<< orphan*/  UINT_MAX ; 
 int ZSTD_CLEVEL_DEFAULT ; 
 size_t ZSTD_compress (char*,size_t,char*,size_t,int) ; 
 size_t ZSTD_compressBound (size_t) ; 
 int /*<<< orphan*/  ZSTD_isError (size_t) ; 
 int ZSTD_maxCLevel () ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 char* erealloc (char*,size_t) ; 
 size_t lzf_compress (char*,size_t,char*,double) ; 
 int redis_serialize (TYPE_1__*,int /*<<< orphan*/ *,char**,size_t*) ; 

int
redis_pack(RedisSock *redis_sock, zval *z, char **val, size_t *val_len)
{
    char *buf;
    int valfree;
    size_t len;

    valfree = redis_serialize(redis_sock, z, &buf, &len);
    switch (redis_sock->compression) {
        case REDIS_COMPRESSION_LZF:
#ifdef HAVE_REDIS_LZF
            {
                char *data;
                uint32_t res;
                double size;

                /* preserve compatibility with PECL lzf_compress margin (greater of 4% and LZF_MARGIN) */
                size = len + MIN(UINT_MAX - len, MAX(LZF_MARGIN, len / 25));
                data = emalloc(size);
                if ((res = lzf_compress(buf, len, data, size)) > 0) {
                    if (valfree) efree(buf);
                    *val = data;
                    *val_len = res;
                    return 1;
                }
                efree(data);
            }
#endif
            break;
        case REDIS_COMPRESSION_ZSTD:
#ifdef HAVE_REDIS_ZSTD
            {
                char *data;
                size_t size;
                int level;

                if (redis_sock->compression_level < 1) {
#ifdef ZSTD_CLEVEL_DEFAULT
                    level = ZSTD_CLEVEL_DEFAULT;
#else
                    level = 3;
#endif
                } else if (redis_sock->compression_level > ZSTD_maxCLevel()) {
                    level = ZSTD_maxCLevel();
                } else {
                    level = redis_sock->compression_level;
                }

                size = ZSTD_compressBound(len);
                data = emalloc(size);
                size = ZSTD_compress(data, size, buf, len, level);
                if (!ZSTD_isError(size)) {
                    if (valfree) efree(buf);
                    data = erealloc(data, size);
                    *val = data;
                    *val_len = size;
                    return 1;
                }
                efree(data);
            }
#endif
            break;
    }
    *val = buf;
    *val_len = len;
    return valfree;
}