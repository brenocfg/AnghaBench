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
struct zip_source {int dummy; } ;
struct zip {int /*<<< orphan*/  error; } ;
struct crc_context {int validate; scalar_t__ crc; scalar_t__ size; scalar_t__* e; scalar_t__ eof; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZIP_ER_INVAL ; 
 int /*<<< orphan*/  ZIP_ER_MEMORY ; 
 int /*<<< orphan*/  _zip_error_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_read ; 
 scalar_t__ malloc (int) ; 
 struct zip_source* zip_source_layered (struct zip*,struct zip_source*,int /*<<< orphan*/ ,struct crc_context*) ; 

struct zip_source *
zip_source_crc(struct zip *za, struct zip_source *src, int validate)
{
    struct crc_context *ctx;

    if (src == NULL) {
	_zip_error_set(&za->error, ZIP_ER_INVAL, 0);
	return NULL;
    }

    if ((ctx=(struct crc_context *)malloc(sizeof(*ctx))) == NULL) {
	_zip_error_set(&za->error, ZIP_ER_MEMORY, 0);
	return NULL;
    }

    ctx->eof = 0;
    ctx->validate = validate;
    ctx->e[0] = ctx->e[1] = 0;
    ctx->size = 0;
    ctx->crc = 0;
    
    return zip_source_layered(za, src, crc_read, ctx);
}