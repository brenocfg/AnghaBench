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
typedef  size_t zend_off_t ;

/* Variables and functions */
 int /*<<< orphan*/ * LOC_GRANDFATHERED ; 
 int /*<<< orphan*/ * LOC_PREFERRED_GRANDFATHERED ; 
 size_t LOC_PREFERRED_GRANDFATHERED_LEN ; 
 char* estrdup (int /*<<< orphan*/ ) ; 
 size_t findOffset (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static char* getPreferredTag(const char* gf_tag)
{
	char* result = NULL;
	zend_off_t grOffset = 0;

	grOffset = findOffset( LOC_GRANDFATHERED ,gf_tag);
	if(grOffset < 0) {
		return NULL;
	}
	if( grOffset < LOC_PREFERRED_GRANDFATHERED_LEN ){
		/* return preferred tag */
		result = estrdup( LOC_PREFERRED_GRANDFATHERED[grOffset] );
	} else {
		/* Return correct grandfathered language tag */
		result = estrdup( LOC_GRANDFATHERED[grOffset] );
	}
	return result;
}