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
struct pprint_mapv_int128 {int dummy; } ;
struct pprint_mapv {int dummy; } ;
typedef  enum pprint_mapv_kind_t { ____Placeholder_pprint_mapv_kind_t } pprint_mapv_kind_t ;

/* Variables and functions */
 int PPRINT_MAPV_KIND_BASIC ; 
 int PPRINT_MAPV_KIND_INT128 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t get_pprint_mapv_size(enum pprint_mapv_kind_t mapv_kind)
{
	if (mapv_kind == PPRINT_MAPV_KIND_BASIC)
		return sizeof(struct pprint_mapv);

#ifdef __SIZEOF_INT128__
	if (mapv_kind == PPRINT_MAPV_KIND_INT128)
		return sizeof(struct pprint_mapv_int128);
#endif

	assert(0);
}