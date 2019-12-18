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
typedef  int /*<<< orphan*/  CreateConversionStmt ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARE_NODE_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_SCALAR_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPARE_STRING_FIELD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  conversion_name ; 
 int /*<<< orphan*/  def ; 
 int /*<<< orphan*/  for_encoding_name ; 
 int /*<<< orphan*/  func_name ; 
 int /*<<< orphan*/  to_encoding_name ; 

__attribute__((used)) static bool
_equalCreateConversionStmt(const CreateConversionStmt *a, const CreateConversionStmt *b)
{
	COMPARE_NODE_FIELD(conversion_name);
	COMPARE_STRING_FIELD(for_encoding_name);
	COMPARE_STRING_FIELD(to_encoding_name);
	COMPARE_NODE_FIELD(func_name);
	COMPARE_SCALAR_FIELD(def);

	return true;
}