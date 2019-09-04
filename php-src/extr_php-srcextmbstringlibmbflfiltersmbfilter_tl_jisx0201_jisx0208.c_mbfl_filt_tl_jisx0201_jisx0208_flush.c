#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode; } ;
typedef  TYPE_1__ mbfl_filt_tl_jisx0201_jisx0208_param ;
struct TYPE_5__ {int cache; int (* output_function ) (scalar_t__,int /*<<< orphan*/ ) ;int (* flush_function ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; scalar_t__ status; scalar_t__ opaque; } ;
typedef  TYPE_2__ mbfl_convert_filter ;

/* Variables and functions */
 scalar_t__* hankana2zenhira_table ; 
 scalar_t__* hankana2zenkana_table ; 
 int stub1 (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub2 (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub3 (int /*<<< orphan*/ ) ; 

int
mbfl_filt_tl_jisx0201_jisx0208_flush(mbfl_convert_filter *filt)
{
	int ret, n;
	int mode = ((mbfl_filt_tl_jisx0201_jisx0208_param *)filt->opaque)->mode;

	ret = 0;
	if (filt->status) {
		n = (filt->cache - 0xff60) & 0x3f;
		if (mode & 0x100) {	/* hankaku kana to zenkaku katakana */
			ret = (*filt->output_function)(0x3000 + hankana2zenkana_table[n], filt->data);
		} else if (mode & 0x200) {	/* hankaku kana to zenkaku hirangana */
			ret = (*filt->output_function)(0x3000 + hankana2zenhira_table[n], filt->data);
		}
		filt->status = 0;
	}

	if (filt->flush_function != NULL) {
		return (*filt->flush_function)(filt->data);
	}

	return ret;
}