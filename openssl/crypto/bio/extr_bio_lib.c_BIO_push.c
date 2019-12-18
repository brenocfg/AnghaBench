#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* prev_bio; struct TYPE_7__* next_bio; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CTRL_PUSH ; 
 int /*<<< orphan*/  BIO_ctrl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

BIO *BIO_push(BIO *b, BIO *bio)
{
    BIO *lb;

    if (b == NULL)
        return bio;
    lb = b;
    while (lb->next_bio != NULL)
        lb = lb->next_bio;
    lb->next_bio = bio;
    if (bio != NULL)
        bio->prev_bio = lb;
    /* called to do internal processing */
    BIO_ctrl(b, BIO_CTRL_PUSH, 0, lb);
    return b;
}