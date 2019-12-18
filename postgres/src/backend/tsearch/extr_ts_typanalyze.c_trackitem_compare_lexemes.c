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
struct TYPE_2__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ TrackItem ;

/* Variables and functions */
 int lexeme_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
trackitem_compare_lexemes(const void *e1, const void *e2)
{
	const TrackItem *const *t1 = (const TrackItem *const *) e1;
	const TrackItem *const *t2 = (const TrackItem *const *) e2;

	return lexeme_compare(&(*t1)->key, &(*t2)->key);
}