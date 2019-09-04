#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* db; int /*<<< orphan*/  disableLookaside; } ;
struct TYPE_5__ {int /*<<< orphan*/  bDisable; } ;
struct TYPE_6__ {TYPE_1__ lookaside; } ;
typedef  TYPE_3__ Parse ;

/* Variables and functions */

__attribute__((used)) static void disableLookaside(Parse *pParse){
  pParse->disableLookaside++;
  pParse->db->lookaside.bDisable++;
}