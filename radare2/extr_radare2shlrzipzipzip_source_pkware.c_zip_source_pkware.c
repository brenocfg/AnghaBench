#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zip_uint8_t ;
typedef  scalar_t__ zip_uint16_t ;
struct zip_source {int dummy; } ;
struct zip {int /*<<< orphan*/  error; } ;
struct trad_pkware {int /*<<< orphan*/ * key; scalar_t__* e; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY0 ; 
 int /*<<< orphan*/  KEY1 ; 
 int /*<<< orphan*/  KEY2 ; 
 int ZIP_CODEC_ENCODE ; 
 scalar_t__ ZIP_EM_TRAD_PKWARE ; 
 int /*<<< orphan*/  ZIP_ER_ENCRNOTSUPP ; 
 int /*<<< orphan*/  ZIP_ER_INVAL ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  decrypt (struct trad_pkware*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  pkware_decrypt ; 
 int /*<<< orphan*/  pkware_free (struct trad_pkware*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 struct zip_source* zip_source_layered (struct zip*,struct zip_source*,int /*<<< orphan*/ ,struct trad_pkware*) ; 

struct zip_source *
zip_source_pkware(struct zip *za, struct zip_source *src,
		  zip_uint16_t em, int flags, const char *password)
{
    struct trad_pkware *ctx;
    struct zip_source *s2;

    if (password == NULL || src == NULL || em != ZIP_EM_TRAD_PKWARE) {
	_zip_error_set(&za->error, ZIP_ER_INVAL, 0);
	return NULL;
    }
    if (flags & ZIP_CODEC_ENCODE) {
	_zip_error_set(&za->error, ZIP_ER_ENCRNOTSUPP, 0);
	return NULL;
    }

    if ((ctx=(struct trad_pkware *)malloc(sizeof(*ctx))) == NULL) {
	_zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
	return NULL;
    }

    ctx->e[0] = ctx->e[1] = 0;

    ctx->key[0] = KEY0;
    ctx->key[1] = KEY1;
    ctx->key[2] = KEY2;
    decrypt(ctx, NULL, (const zip_uint8_t *)password, strlen(password), 1);

    if ((s2=zip_source_layered(za, src, pkware_decrypt, ctx)) == NULL) {
	pkware_free(ctx);
	return NULL;
    }

    return s2;
}