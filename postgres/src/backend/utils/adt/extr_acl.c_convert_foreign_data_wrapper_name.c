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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  Oid ;

/* Variables and functions */
 int /*<<< orphan*/  get_foreign_data_wrapper_oid (char*,int) ; 
 char* text_to_cstring (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Oid
convert_foreign_data_wrapper_name(text *fdwname)
{
	char	   *fdwstr = text_to_cstring(fdwname);

	return get_foreign_data_wrapper_oid(fdwstr, false);
}