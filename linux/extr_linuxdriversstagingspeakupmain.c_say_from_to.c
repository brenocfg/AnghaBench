#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u_long ;
typedef  int /*<<< orphan*/  u_char ;
struct vc_data {int vc_size_row; } ;
struct TYPE_2__ {int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 char SPACE ; 
 char* buf ; 
 int /*<<< orphan*/  get_attributes (struct vc_data*,int /*<<< orphan*/ *) ; 
 char get_char (struct vc_data*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spk_attr ; 
 int /*<<< orphan*/  spk_old_attr ; 
 TYPE_1__* spk_punc_info ; 
 int /*<<< orphan*/  spk_punc_mask ; 
 size_t spk_reading_punc ; 
 int /*<<< orphan*/  spkup_write (char*,int) ; 

__attribute__((used)) static int say_from_to(struct vc_data *vc, u_long from, u_long to,
		       int read_punc)
{
	int i = 0;
	u_char tmp;
	u_short saved_punc_mask = spk_punc_mask;

	spk_old_attr = spk_attr;
	spk_attr = get_attributes(vc, (u_short *)from);
	while (from < to) {
		buf[i++] = get_char(vc, (u_short *)from, &tmp);
		from += 2;
		if (i >= vc->vc_size_row)
			break;
	}
	for (--i; i >= 0; i--)
		if (buf[i] != SPACE)
			break;
	buf[++i] = SPACE;
	buf[++i] = '\0';
	if (i < 1)
		return i;
	if (read_punc)
		spk_punc_mask = spk_punc_info[spk_reading_punc].mask;
	spkup_write(buf, i);
	if (read_punc)
		spk_punc_mask = saved_punc_mask;
	return i - 1;
}