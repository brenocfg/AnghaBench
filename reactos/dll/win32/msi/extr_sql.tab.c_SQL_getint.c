#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* command; size_t n; size_t len; } ;
typedef  TYPE_1__ SQL_input ;
typedef  char* LPCWSTR ;
typedef  size_t INT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 

INT SQL_getint( void *info )
{
    SQL_input* sql = (SQL_input*) info;
    LPCWSTR p = &sql->command[sql->n];
    INT i, r = 0;

    for( i=0; i<sql->len; i++ )
    {
        if( '0' > p[i] || '9' < p[i] )
        {
            ERR("should only be numbers here!\n");
            break;
        }
        r = (p[i]-'0') + r*10;
    }

    return r;
}