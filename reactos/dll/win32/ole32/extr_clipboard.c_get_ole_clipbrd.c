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
struct oletls {int /*<<< orphan*/  ole_inits; } ;
typedef  int /*<<< orphan*/  ole_clipbrd ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 struct oletls* COM_CurrentInfo () ; 
 int /*<<< orphan*/  CO_E_NOTINITIALIZED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * theOleClipboard ; 

__attribute__((used)) static inline HRESULT get_ole_clipbrd(ole_clipbrd **clipbrd)
{
    struct oletls *info = COM_CurrentInfo();
    *clipbrd = NULL;

    if(!info->ole_inits)
        return CO_E_NOTINITIALIZED;
    *clipbrd = theOleClipboard;

    return S_OK;
}