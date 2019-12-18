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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int ut32 ;

/* Variables and functions */
 int NB_PRIV_FIELDS ; 
 int /*<<< orphan*/ * parse_next_rsa_field (int /*<<< orphan*/  const*,int*) ; 

__attribute__((used)) static int check_rsa_fields(const ut8* start) {
#define NB_PRIV_FIELDS 10
	ut32 len = 0;
	int i;
	// skip sequence field
	ut8 const* ptr = parse_next_rsa_field (start, &len);

	if (!len || len > 1024) {
		return false;
	}
	for (i = 0; i < NB_PRIV_FIELDS; i++) {
		if (!(ptr = parse_next_rsa_field (ptr, &len))) {
			return false;
		}
	}
	return true;
}