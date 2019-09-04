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
typedef  scalar_t__ u32 ;
struct xt_match {scalar_t__ revision; scalar_t__ family; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ NFPROTO_UNSPEC ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static bool nft_match_cmp(const struct xt_match *match,
			  const char *name, u32 rev, u32 family)
{
	return strcmp(match->name, name) == 0 && match->revision == rev &&
	       (match->family == NFPROTO_UNSPEC || match->family == family);
}