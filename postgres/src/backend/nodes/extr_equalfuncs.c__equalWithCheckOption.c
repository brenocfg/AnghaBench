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
typedef  int /*<<< orphan*/  WithCheckOption ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cascaded ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  polname ; 
 int /*<<< orphan*/  qual ; 
 int /*<<< orphan*/  relname ; 

__attribute__((used)) static bool
_equalWithCheckOption(const WithCheckOption *a, const WithCheckOption *b)
{
	COMPARE_SCALAR_FIELD(kind);
	COMPARE_STRING_FIELD(relname);
	COMPARE_STRING_FIELD(polname);
	COMPARE_NODE_FIELD(qual);
	COMPARE_SCALAR_FIELD(cascaded);

	return true;
}