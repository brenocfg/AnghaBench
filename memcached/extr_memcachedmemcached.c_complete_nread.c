#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ protocol; } ;
typedef  TYPE_1__ conn ;

/* Variables and functions */
 scalar_t__ ascii_prot ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ binary_prot ; 
 int /*<<< orphan*/  complete_nread_ascii (TYPE_1__*) ; 
 int /*<<< orphan*/  complete_nread_binary (TYPE_1__*) ; 

__attribute__((used)) static void complete_nread(conn *c) {
    assert(c != NULL);
    assert(c->protocol == ascii_prot
           || c->protocol == binary_prot);

    if (c->protocol == ascii_prot) {
        complete_nread_ascii(c);
    } else if (c->protocol == binary_prot) {
        complete_nread_binary(c);
    }
}