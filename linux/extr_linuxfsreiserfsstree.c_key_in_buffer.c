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
struct treepath {scalar_t__ path_length; } ;
struct super_block {int dummy; } ;
struct cpu_key {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  b_bdev; } ;

/* Variables and functions */
 scalar_t__ FIRST_PATH_ELEMENT_OFFSET ; 
 scalar_t__ MAX_HEIGHT ; 
 TYPE_1__* PATH_PLAST_BUFFER (struct treepath*) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int comp_keys (int /*<<< orphan*/ ,struct cpu_key const*) ; 
 int /*<<< orphan*/  get_lkey (struct treepath*,struct super_block*) ; 
 int /*<<< orphan*/  get_rkey (struct treepath*,struct super_block*) ; 

__attribute__((used)) static inline int key_in_buffer(
				/* Path which should be checked. */
				struct treepath *chk_path,
				/* Key which should be checked. */
				const struct cpu_key *key,
				struct super_block *sb
    )
{

	RFALSE(!key || chk_path->path_length < FIRST_PATH_ELEMENT_OFFSET
	       || chk_path->path_length > MAX_HEIGHT,
	       "PAP-5050: pointer to the key(%p) is NULL or invalid path length(%d)",
	       key, chk_path->path_length);
	RFALSE(!PATH_PLAST_BUFFER(chk_path)->b_bdev,
	       "PAP-5060: device must not be NODEV");

	if (comp_keys(get_lkey(chk_path, sb), key) == 1)
		/* left delimiting key is bigger, that the key we look for */
		return 0;
	/*  if ( comp_keys(key, get_rkey(chk_path, sb)) != -1 ) */
	if (comp_keys(get_rkey(chk_path, sb), key) != 1)
		/* key must be less than right delimitiing key */
		return 0;
	return 1;
}