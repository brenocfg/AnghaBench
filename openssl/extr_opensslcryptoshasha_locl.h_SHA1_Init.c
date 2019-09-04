#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  h4; int /*<<< orphan*/  h3; int /*<<< orphan*/  h2; int /*<<< orphan*/  h1; int /*<<< orphan*/  h0; } ;
typedef  TYPE_1__ SHA_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_DATA_h0 ; 
 int /*<<< orphan*/  INIT_DATA_h1 ; 
 int /*<<< orphan*/  INIT_DATA_h2 ; 
 int /*<<< orphan*/  INIT_DATA_h3 ; 
 int /*<<< orphan*/  INIT_DATA_h4 ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int HASH_INIT(SHA_CTX *c)
{
    memset(c, 0, sizeof(*c));
    c->h0 = INIT_DATA_h0;
    c->h1 = INIT_DATA_h1;
    c->h2 = INIT_DATA_h2;
    c->h3 = INIT_DATA_h3;
    c->h4 = INIT_DATA_h4;
    return 1;
}