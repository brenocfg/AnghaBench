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
typedef  int BOOL ;

/* Variables and functions */
 int lex_Composed_Vowel ; 
 int lex_Matra_above ; 
 int lex_Matra_below ; 
 int lex_Matra_post ; 
 int lex_Matra_pre ; 

__attribute__((used)) static inline BOOL is_matra( int type )
{
    return (type == lex_Matra_above || type == lex_Matra_below ||
            type == lex_Matra_pre || type == lex_Matra_post ||
            type == lex_Composed_Vowel);
}