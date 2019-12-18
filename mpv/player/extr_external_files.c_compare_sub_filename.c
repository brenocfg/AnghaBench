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
struct subfn {int /*<<< orphan*/  fname; } ;

/* Variables and functions */
 int strcoll (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int compare_sub_filename(const void *a, const void *b)
{
    const struct subfn *s1 = a;
    const struct subfn *s2 = b;
    return strcoll(s1->fname, s2->fname);
}