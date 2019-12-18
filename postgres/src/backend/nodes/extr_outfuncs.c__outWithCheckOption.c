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
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  WCOKind ; 
 int /*<<< orphan*/  WRITE_BOOL_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ENUM_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_NODE_TYPE (char*) ; 
 int /*<<< orphan*/  WRITE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cascaded ; 
 int /*<<< orphan*/  kind ; 
 int /*<<< orphan*/  polname ; 
 int /*<<< orphan*/  qual ; 
 int /*<<< orphan*/  relname ; 

__attribute__((used)) static void
_outWithCheckOption(StringInfo str, const WithCheckOption *node)
{
	WRITE_NODE_TYPE("WITHCHECKOPTION");

	WRITE_ENUM_FIELD(kind, WCOKind);
	WRITE_STRING_FIELD(relname);
	WRITE_STRING_FIELD(polname);
	WRITE_NODE_FIELD(qual);
	WRITE_BOOL_FIELD(cascaded);
}