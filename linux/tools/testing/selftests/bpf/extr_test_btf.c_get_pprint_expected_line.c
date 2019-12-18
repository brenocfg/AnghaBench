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
typedef  int /*<<< orphan*/  uint64_t ;
struct pprint_mapv_int128 {int bits80; int ui128; scalar_t__ bits3; scalar_t__ si128b; scalar_t__ si128a; } ;
struct pprint_mapv {int ui32; int si32; int unused_bits2a; int bits28; int unused_bits2b; int ui64; int* ui8a; size_t aenum; int /*<<< orphan*/ ** si8_4; int /*<<< orphan*/  bits2c; int /*<<< orphan*/  ui32b; } ;
typedef  int ssize_t ;
typedef  enum pprint_mapv_kind_t { ____Placeholder_pprint_mapv_kind_t } pprint_mapv_kind_t ;

/* Variables and functions */
 int PPRINT_MAPV_KIND_BASIC ; 
 int PPRINT_MAPV_KIND_INT128 ; 
 int /*<<< orphan*/ * pprint_enum_str ; 
 int snprintf (char*,int,char*,char*,int,int,int,int,int,int,int,int,...) ; 

ssize_t get_pprint_expected_line(enum pprint_mapv_kind_t mapv_kind,
				 char *expected_line, ssize_t line_size,
				 bool percpu_map, unsigned int next_key,
				 int cpu, void *mapv)
{
	ssize_t nexpected_line = -1;

	if (mapv_kind == PPRINT_MAPV_KIND_BASIC) {
		struct pprint_mapv *v = mapv;

		nexpected_line = snprintf(expected_line, line_size,
					  "%s%u: {%u,0,%d,0x%x,0x%x,0x%x,"
					  "{%lu|[%u,%u,%u,%u,%u,%u,%u,%u]},%s,"
					  "%u,0x%x,[[%d,%d],[%d,%d]]}\n",
					  percpu_map ? "\tcpu" : "",
					  percpu_map ? cpu : next_key,
					  v->ui32, v->si32,
					  v->unused_bits2a,
					  v->bits28,
					  v->unused_bits2b,
					  v->ui64,
					  v->ui8a[0], v->ui8a[1],
					  v->ui8a[2], v->ui8a[3],
					  v->ui8a[4], v->ui8a[5],
					  v->ui8a[6], v->ui8a[7],
					  pprint_enum_str[v->aenum],
					  v->ui32b,
					  v->bits2c,
					  v->si8_4[0][0], v->si8_4[0][1],
					  v->si8_4[1][0], v->si8_4[1][1]);
	}

#ifdef __SIZEOF_INT128__
	if (mapv_kind == PPRINT_MAPV_KIND_INT128) {
		struct pprint_mapv_int128 *v = mapv;

		nexpected_line = snprintf(expected_line, line_size,
					  "%s%u: {0x%lx,0x%lx,0x%lx,"
					  "0x%lx%016lx,0x%lx%016lx}\n",
					  percpu_map ? "\tcpu" : "",
					  percpu_map ? cpu : next_key,
					  (uint64_t)v->si128a,
					  (uint64_t)v->si128b,
					  (uint64_t)v->bits3,
					  (uint64_t)(v->bits80 >> 64),
					  (uint64_t)v->bits80,
					  (uint64_t)(v->ui128 >> 64),
					  (uint64_t)v->ui128);
	}
#endif

	return nexpected_line;
}