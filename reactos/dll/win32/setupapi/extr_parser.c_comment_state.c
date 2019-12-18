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
struct parser {int dummy; } ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  is_eol (struct parser*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  pop_state (struct parser*) ; 

__attribute__((used)) static const WCHAR *comment_state( struct parser *parser, const WCHAR *pos )
{
    const WCHAR *p = pos;

    while (!is_eol( parser, p )) p++;
    pop_state( parser );
    return p;
}