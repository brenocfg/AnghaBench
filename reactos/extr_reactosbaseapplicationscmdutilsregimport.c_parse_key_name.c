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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HKEY ;

/* Variables and functions */
 int /*<<< orphan*/  path_get_rootkey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strchrW (int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static HKEY parse_key_name(WCHAR *key_name, WCHAR **key_path)
{
    if (!key_name) return 0;

    *key_path = strchrW(key_name, '\\');
    if (*key_path) (*key_path)++;

    return path_get_rootkey(key_name);
}