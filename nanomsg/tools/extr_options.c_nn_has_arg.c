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
struct nn_option {int type; } ;

/* Variables and functions */
#define  NN_OPT_BLOB 139 
#define  NN_OPT_DECREMENT 138 
#define  NN_OPT_ENUM 137 
#define  NN_OPT_FLOAT 136 
#define  NN_OPT_HELP 135 
#define  NN_OPT_INCREMENT 134 
#define  NN_OPT_INT 133 
#define  NN_OPT_LIST_APPEND 132 
#define  NN_OPT_LIST_APPEND_FMT 131 
#define  NN_OPT_READ_FILE 130 
#define  NN_OPT_SET_ENUM 129 
#define  NN_OPT_STRING 128 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nn_has_arg (struct nn_option *opt)
{
    switch (opt->type) {
        case NN_OPT_INCREMENT:
        case NN_OPT_DECREMENT:
        case NN_OPT_SET_ENUM:
        case NN_OPT_HELP:
            return 0;
        case NN_OPT_ENUM:
        case NN_OPT_STRING:
        case NN_OPT_BLOB:
        case NN_OPT_FLOAT:
        case NN_OPT_INT:
        case NN_OPT_LIST_APPEND:
        case NN_OPT_LIST_APPEND_FMT:
        case NN_OPT_READ_FILE:
            return 1;
    }
    nn_assert (0);
}