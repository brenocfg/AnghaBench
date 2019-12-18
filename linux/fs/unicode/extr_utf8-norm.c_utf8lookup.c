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
typedef  int /*<<< orphan*/  utf8leaf_t ;
struct utf8data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/ * utf8nlookup (struct utf8data const*,unsigned char*,char const*,size_t) ; 

__attribute__((used)) static utf8leaf_t *utf8lookup(const struct utf8data *data,
			      unsigned char *hangul, const char *s)
{
	return utf8nlookup(data, hangul, s, (size_t)-1);
}