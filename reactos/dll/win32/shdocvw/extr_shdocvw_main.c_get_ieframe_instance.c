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
typedef  char WCHAR ;
typedef  scalar_t__ HINSTANCE ;

/* Variables and functions */
 scalar_t__ LoadLibraryW (char const*) ; 
 scalar_t__ ieframe_instance ; 

__attribute__((used)) static HINSTANCE get_ieframe_instance(void)
{
    static const WCHAR ieframe_dllW[] = {'i','e','f','r','a','m','e','.','d','l','l',0};

    if(!ieframe_instance)
        ieframe_instance = LoadLibraryW(ieframe_dllW);

    return ieframe_instance;
}