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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */
 int ARRAY_SIZE (char const* const*) ; 
 int find_idx_in_nid_list (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const char *check_output_sfx(hda_nid_t nid, const hda_nid_t *pins,
				    int num_pins, int *indexp)
{
	static const char * const channel_sfx[] = {
		" Front", " Surround", " CLFE", " Side"
	};
	int i;

	i = find_idx_in_nid_list(nid, pins, num_pins);
	if (i < 0)
		return NULL;
	if (num_pins == 1)
		return "";
	if (num_pins > ARRAY_SIZE(channel_sfx)) {
		if (indexp)
			*indexp = i;
		return "";
	}
	return channel_sfx[i];
}