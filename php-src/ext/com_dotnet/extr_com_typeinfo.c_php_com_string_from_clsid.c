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
typedef  int /*<<< orphan*/  LPOLESTR ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  LocalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StringFromCLSID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 char* php_com_olestring_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static char *php_com_string_from_clsid(const CLSID *clsid, int codepage)
{
	LPOLESTR ole_clsid;
	char *clsid_str;

	StringFromCLSID(clsid, &ole_clsid);
	clsid_str = php_com_olestring_to_string(ole_clsid, NULL, codepage);
	LocalFree(ole_clsid);

	return clsid_str;
}