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
typedef  int /*<<< orphan*/ * LPCWSTR ;
typedef  int INT ;

/* Variables and functions */
#define  COND_ILHS 133 
#define  COND_IRHS 132 
#define  COND_ISS 131 
#define  COND_LHS 130 
#define  COND_RHS 129 
#define  COND_SS 128 
 int /*<<< orphan*/  ERR (char*) ; 
 int atoiW (int /*<<< orphan*/ *) ; 
 int compare_int (int,int,int) ; 
 scalar_t__ str_is_number (int /*<<< orphan*/ *) ; 
 int strlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strncmpiW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strstrW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strstriW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static INT compare_substring( LPCWSTR a, INT operator, LPCWSTR b )
{
    int lhs, rhs;

    /* substring operators return 0 if LHS is missing */
    if (!a || !*a)
        return 0;

    /* substring operators return 1 if RHS is missing */
    if (!b || !*b)
        return 1;

    /* if both strings contain only numbers, use integer comparison */
    lhs = atoiW(a);
    rhs = atoiW(b);
    if (str_is_number(a) && str_is_number(b))
        return compare_int( lhs, operator, rhs );

    switch (operator)
    {
    case COND_SS:
        return strstrW( a, b ) != 0;
    case COND_ISS:
        return strstriW( a, b ) != 0;
    case COND_LHS:
    {
        int l = strlenW( a );
        int r = strlenW( b );
        if (r > l) return 0;
        return !strncmpW( a, b, r );
    }
    case COND_RHS:
    {
        int l = strlenW( a );
        int r = strlenW( b );
        if (r > l) return 0;
        return !strncmpW( a + (l - r), b, r );
    }
    case COND_ILHS:
    {
        int l = strlenW( a );
        int r = strlenW( b );
        if (r > l) return 0;
        return !strncmpiW( a, b, r );
    }
    case COND_IRHS:
    {
        int l = strlenW( a );
        int r = strlenW( b );
        if (r > l) return 0;
        return !strncmpiW( a + (l - r), b, r );
    }
    default:
        ERR("invalid substring operator\n");
        return 0;
    }
    return 0;
}