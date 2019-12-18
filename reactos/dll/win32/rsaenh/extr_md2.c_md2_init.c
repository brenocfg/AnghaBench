#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ curlen; int /*<<< orphan*/  buf; int /*<<< orphan*/  chksum; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ md2_state ;

/* Variables and functions */
 int CRYPT_OK ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int md2_init(md2_state *md2)
{
   /* MD2 uses a zero'ed state... */
   memset(md2->X, 0, sizeof(md2->X));
   memset(md2->chksum, 0, sizeof(md2->chksum));
   memset(md2->buf, 0, sizeof(md2->buf));
   md2->curlen = 0;
   return CRYPT_OK;
}