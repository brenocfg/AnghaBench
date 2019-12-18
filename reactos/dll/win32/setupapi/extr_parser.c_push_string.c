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
struct inf_file {int /*<<< orphan*/ * string_pos; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  strcpyW (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ strlenW (int /*<<< orphan*/ *) ; 

__attribute__((used)) static WCHAR *push_string( struct inf_file *file, const WCHAR *string )
{
    WCHAR *ret = file->string_pos;
    strcpyW( ret, string );
    file->string_pos += strlenW( ret ) + 1;
    return ret;
}