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
typedef  int /*<<< orphan*/  u8 ;
struct aa_ext {void* pos; } ;

/* Variables and functions */
 int /*<<< orphan*/  AA_U8 ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inbounds (struct aa_ext*,int) ; 
 scalar_t__ unpack_nameX (struct aa_ext*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool unpack_u8(struct aa_ext *e, u8 *data, const char *name)
{
	void *pos = e->pos;

	if (unpack_nameX(e, AA_U8, name)) {
		if (!inbounds(e, sizeof(u8)))
			goto fail;
		if (data)
			*data = get_unaligned((u8 *)e->pos);
		e->pos += sizeof(u8);
		return 1;
	}

fail:
	e->pos = pos;
	return 0;
}