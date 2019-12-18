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
struct TYPE_2__ {unsigned char id; scalar_t__ (* parse ) (char const**) ;} ;

/* Variables and functions */
 unsigned char EVAL_OPERATOR_NOP ; 
 int eval_precedence (unsigned char) ; 
 TYPE_1__* operator_parsers ; 
 int /*<<< orphan*/  skip_spaces (char const**) ; 
 scalar_t__ stub1 (char const**) ; 

__attribute__((used)) static inline unsigned char parse_operator(const char **string, int *precedence) {
    skip_spaces(string);

    int i;
    for(i = 0 ; operator_parsers[i].parse != NULL ; i++)
        if(operator_parsers[i].parse(string)) {
            if(precedence) *precedence = eval_precedence(operator_parsers[i].id);
            return operator_parsers[i].id;
        }

    return EVAL_OPERATOR_NOP;
}