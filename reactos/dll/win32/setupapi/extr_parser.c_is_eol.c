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
struct parser {char const* end; } ;
typedef  char WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 char const CONTROL_Z ; 

__attribute__((used)) static inline BOOL is_eol( const struct parser *parser, const WCHAR *ptr )
{
    return (ptr >= parser->end || *ptr == CONTROL_Z || *ptr == '\n');
}