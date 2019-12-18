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
struct RTFTable {int gapH; scalar_t__ leftEdge; scalar_t__ numCellsDefined; int /*<<< orphan*/  border; int /*<<< orphan*/  cells; } ;
struct TYPE_3__ {int /*<<< orphan*/  bEmulateVersion10; } ;
typedef  TYPE_1__ ME_TextEditor ;

/* Variables and functions */
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ ,int) ; 

void ME_InitTableDef(ME_TextEditor *editor, struct RTFTable *tableDef)
{
  ZeroMemory(tableDef->cells, sizeof(tableDef->cells));
  ZeroMemory(tableDef->border, sizeof(tableDef->border));
  tableDef->numCellsDefined = 0;
  tableDef->leftEdge = 0;
  if (!editor->bEmulateVersion10) /* v4.1 */
    tableDef->gapH = 10;
  else /* v1.0 - 3.0 */
    tableDef->gapH = 0;
}