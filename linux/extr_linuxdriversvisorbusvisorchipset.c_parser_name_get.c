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
struct visor_controlvm_parameters_header {int name_offset; scalar_t__ name_length; } ;
struct parser_context {unsigned long param_bytes; char* curr; scalar_t__ bytes_remaining; struct visor_controlvm_parameters_header data; } ;

/* Variables and functions */
 void* parser_string_get (char*,scalar_t__) ; 

__attribute__((used)) static void *parser_name_get(struct parser_context *ctx)
{
	struct visor_controlvm_parameters_header *phdr;

	phdr = &ctx->data;
	if ((unsigned long)phdr->name_offset +
	    (unsigned long)phdr->name_length > ctx->param_bytes)
		return NULL;
	ctx->curr = (char *)&phdr + phdr->name_offset;
	ctx->bytes_remaining = phdr->name_length;
	return parser_string_get(ctx->curr, phdr->name_length);
}