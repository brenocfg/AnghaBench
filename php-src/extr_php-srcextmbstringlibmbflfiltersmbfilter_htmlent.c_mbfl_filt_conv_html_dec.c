#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int code; scalar_t__ name; } ;
typedef  TYPE_1__ mbfl_html_entity_entry ;
struct TYPE_6__ {int status; int /*<<< orphan*/  data; int /*<<< orphan*/  (* output_function ) (int,int /*<<< orphan*/ ) ;scalar_t__ opaque; } ;
typedef  TYPE_2__ mbfl_convert_filter ;

/* Variables and functions */
 int /*<<< orphan*/  CK (int /*<<< orphan*/ ) ; 
 int html_enc_buffer_size ; 
 int /*<<< orphan*/  html_entity_chars ; 
 int /*<<< orphan*/  mbfl_filt_conv_html_dec_flush (TYPE_2__*) ; 
 scalar_t__ mbfl_html_entity_list ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char*,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ ) ; 

int mbfl_filt_conv_html_dec(int c, mbfl_convert_filter *filter)
{
	int  pos, ent = 0;
	mbfl_html_entity_entry *entity;
	char *buffer = (char*)filter->opaque;

	if (!filter->status) {
		if (c == '&' ) {
			filter->status = 1;
			buffer[0] = '&';
		} else {
			CK((*filter->output_function)(c, filter->data));
		}
	} else {
		if (c == ';') {
			if (buffer[1]=='#') {
				if (filter->status > 2 && (buffer[2] == 'x' || buffer[2] == 'X')) {
					if (filter->status > 3) {
						/* numeric entity */
						for (pos=3; pos<filter->status; pos++) {
							int v =  buffer[pos];
							if (v >= '0' && v <= '9') {
								v = v - '0';
							} else if (v >= 'A' && v <= 'F') {
								v = v - 'A' + 10;
							} else if (v >= 'a' && v <= 'f') {
								v = v - 'a' + 10;
							} else {
								ent = -1;
								break;
							}
							ent = ent * 16 + v;
						}
					} else {
						ent = -1;
					}
				} else {
					/* numeric entity */
					if (filter->status > 2) {
						for (pos=2; pos<filter->status; pos++) {
							int v = buffer[pos];
							if (v >= '0' && v <= '9') {
								v = v - '0';
							} else {
								ent = -1;
								break;
							}
							ent = ent*10 + v;
						}
					} else {
						ent = -1;
					}
				}
				if (ent >= 0 && ent < 0x110000) {
					CK((*filter->output_function)(ent, filter->data));
				} else {
					for (pos = 0; pos < filter->status; pos++) {
						CK((*filter->output_function)(buffer[pos], filter->data));
					}
					CK((*filter->output_function)(c, filter->data));
				}
				filter->status = 0;
				/*php_error_docref("ref.mbstring", E_NOTICE, "mbstring decoded '%s'=%d", buffer, ent);*/
			} else {
				/* named entity */
				buffer[filter->status] = 0;
				entity = (mbfl_html_entity_entry *)mbfl_html_entity_list;
				while (entity->name) {
					if (!strcmp(buffer+1, entity->name))	{
						ent = entity->code;
						break;
					}
					entity++;
				}
				if (ent) {
					/* decoded */
					CK((*filter->output_function)(ent, filter->data));
					filter->status = 0;
					/*php_error_docref("ref.mbstring", E_NOTICE,"mbstring decoded '%s'=%d", buffer, ent);*/
				} else {
					/* failure */
					buffer[filter->status++] = ';';
					buffer[filter->status] = 0;
					/* php_error_docref("ref.mbstring", E_WARNING, "mbstring cannot decode '%s'", buffer); */
					mbfl_filt_conv_html_dec_flush(filter);
				}
			}
		} else {
			/* add character */
			buffer[filter->status++] = c;
			/* add character and check */
			if (!strchr(html_entity_chars, c) || filter->status+1==html_enc_buffer_size || (c=='#' && filter->status>2))
			{
				/* illegal character or end of buffer */
				if (c=='&')
					filter->status--;
				buffer[filter->status] = 0;
				/* php_error_docref("ref.mbstring", E_WARNING, "mbstring cannot decode '%s'", buffer)l */
				mbfl_filt_conv_html_dec_flush(filter);
				if (c=='&')
				{
					buffer[filter->status++] = '&';
				}
			}
		}
	}
	return c;
}