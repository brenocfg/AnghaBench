#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* prev_bio; struct TYPE_8__* next_bio; } ;
struct TYPE_7__ {TYPE_2__* next_bio; } ;
typedef  TYPE_2__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_POP ; 
 int /*<<< orphan*/  BIO_ctrl (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

BIO *BIO_pop(BIO *b)
{
    BIO *ret;

    if (b == NULL)
        return NULL;
    ret = b->next_bio;

    BIO_ctrl(b, BIO_CTRL_POP, 0, b);

    if (b->prev_bio != NULL)
        b->prev_bio->next_bio = b->next_bio;
    if (b->next_bio != NULL)
        b->next_bio->prev_bio = b->prev_bio;

    b->next_bio = NULL;
    b->prev_bio = NULL;
    return ret;
}