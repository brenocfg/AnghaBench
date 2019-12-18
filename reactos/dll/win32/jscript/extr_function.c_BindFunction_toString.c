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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * jsstr_alloc (char const*) ; 

__attribute__((used)) static HRESULT BindFunction_toString(FunctionInstance *function, jsstr_t **ret)
{
    static const WCHAR native_functionW[] =
        {'\n','f','u','n','c','t','i','o','n','(',')',' ','{','\n',
         ' ',' ',' ',' ','[','n','a','t','i','v','e',' ','c','o','d','e',']','\n',
         '}','\n',0};

    *ret = jsstr_alloc(native_functionW);
    return *ret ? S_OK : E_OUTOFMEMORY;
}