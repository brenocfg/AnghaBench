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
struct bitmask {unsigned int size; scalar_t__ maskp; } ;

/* Variables and functions */
 scalar_t__ calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (struct bitmask*) ; 
 int /*<<< orphan*/  longsperbits (unsigned int) ; 
 struct bitmask* malloc (int) ; 

struct bitmask *bitmask_alloc(unsigned int n)
{
	struct bitmask *bmp;

	bmp = malloc(sizeof(*bmp));
	if (bmp == 0)
		return 0;
	bmp->size = n;
	bmp->maskp = calloc(longsperbits(n), sizeof(unsigned long));
	if (bmp->maskp == 0) {
		free(bmp);
		return 0;
	}
	return bmp;
}