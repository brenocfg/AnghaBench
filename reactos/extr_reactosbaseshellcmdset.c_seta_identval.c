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
typedef  int /*<<< orphan*/  LPCTSTR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  GetEnvVarOrSpecial (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _tcstol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static INT
seta_identval(LPCTSTR ident)
{
    LPCTSTR identVal = GetEnvVarOrSpecial ( ident );
    if ( !identVal )
        return 0;
    else
        return _tcstol ( identVal, NULL, 0 );
}