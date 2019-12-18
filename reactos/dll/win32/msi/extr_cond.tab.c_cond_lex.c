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
struct cond_str {int dummy; } ;
typedef  int /*<<< orphan*/  COND_input ;

/* Variables and functions */
 int COND_GetOne (struct cond_str*,int /*<<< orphan*/ *) ; 
 int COND_SPACE ; 

__attribute__((used)) static int cond_lex( void *COND_lval, COND_input *cond )
{
    int rc;
    struct cond_str *str = COND_lval;

    do {
        rc = COND_GetOne( str, cond );
    } while (rc == COND_SPACE);
    
    return rc;
}