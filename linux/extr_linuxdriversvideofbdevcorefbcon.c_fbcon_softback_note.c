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
typedef  int /*<<< orphan*/  u16 ;
struct vc_data {scalar_t__ vc_num; int vc_size_row; scalar_t__ vc_origin; } ;

/* Variables and functions */
 unsigned short* advance_row (unsigned short*,int) ; 
 scalar_t__ fg_console ; 
 int /*<<< orphan*/  scr_memcpyw (int /*<<< orphan*/ *,unsigned short*,int) ; 
 scalar_t__ softback_buf ; 
 scalar_t__ softback_curr ; 
 scalar_t__ softback_end ; 
 scalar_t__ softback_in ; 
 scalar_t__ softback_top ; 

__attribute__((used)) static inline void fbcon_softback_note(struct vc_data *vc, int t,
				       int count)
{
	unsigned short *p;

	if (vc->vc_num != fg_console)
		return;
	p = (unsigned short *) (vc->vc_origin + t * vc->vc_size_row);

	while (count) {
		scr_memcpyw((u16 *) softback_in, p, vc->vc_size_row);
		count--;
		p = advance_row(p, 1);
		softback_in += vc->vc_size_row;
		if (softback_in == softback_end)
			softback_in = softback_buf;
		if (softback_in == softback_top) {
			softback_top += vc->vc_size_row;
			if (softback_top == softback_end)
				softback_top = softback_buf;
		}
	}
	softback_curr = softback_in;
}