#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  void* u_char ;
struct TYPE_3__ {int encrypt; void** iv; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ ngx_rtmp_mpegts_file_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;

/* Variables and functions */
 scalar_t__ AES_set_encrypt_key (void**,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_memzero (void**,int) ; 

ngx_int_t
ngx_rtmp_mpegts_init_encryption(ngx_rtmp_mpegts_file_t *file,
    u_char *key, size_t key_len, uint64_t iv)
{
    if (AES_set_encrypt_key(key, key_len * 8, &file->key)) {
        return NGX_ERROR;
    }

    ngx_memzero(file->iv, 8);

    file->iv[8]  = (u_char) (iv >> 56);
    file->iv[9]  = (u_char) (iv >> 48);
    file->iv[10] = (u_char) (iv >> 40);
    file->iv[11] = (u_char) (iv >> 32);
    file->iv[12] = (u_char) (iv >> 24);
    file->iv[13] = (u_char) (iv >> 16);
    file->iv[14] = (u_char) (iv >> 8);
    file->iv[15] = (u_char) (iv);

    file->encrypt = 1;

    return NGX_OK;
}