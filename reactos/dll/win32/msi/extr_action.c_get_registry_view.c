#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int Attributes; } ;
typedef  int /*<<< orphan*/  REGSAM ;
typedef  TYPE_1__ MSICOMPONENT ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_WOW64_32KEY ; 
 int /*<<< orphan*/  KEY_WOW64_64KEY ; 
 scalar_t__ is_64bit ; 
 scalar_t__ is_wow64 ; 
 int msidbComponentAttributes64bit ; 

__attribute__((used)) static inline REGSAM get_registry_view( const MSICOMPONENT *comp )
{
    REGSAM view = 0;
    if (is_wow64 || is_64bit)
        view |= (comp->Attributes & msidbComponentAttributes64bit) ? KEY_WOW64_64KEY : KEY_WOW64_32KEY;
    return view;
}