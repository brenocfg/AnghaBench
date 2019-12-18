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
typedef  int /*<<< orphan*/  u64 ;
struct aa_ext {void* pos; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int /*<<< orphan*/  AA_U64 ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inbounds (struct aa_ext*,int) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ unpack_nameX (struct aa_ext*,int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool unpack_u64(struct aa_ext *e, u64 *data, const char *name)
{
	void *pos = e->pos;

	if (unpack_nameX(e, AA_U64, name)) {
		if (!inbounds(e, sizeof(u64)))
			goto fail;
		if (data)
			*data = le64_to_cpu(get_unaligned((__le64 *) e->pos));
		e->pos += sizeof(u64);
		return 1;
	}

fail:
	e->pos = pos;
	return 0;
}