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
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  sqlite3_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_value_int (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void errlogFunc(
  sqlite3_context *context,
  int argc,
  sqlite3_value **argv
){
  UNUSED_PARAMETER(argc);
  UNUSED_PARAMETER(context);
  sqlite3_log(sqlite3_value_int(argv[0]), "%s", sqlite3_value_text(argv[1]));
}