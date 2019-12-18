#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int nCharOfs; } ;
struct TYPE_7__ {int nCharOfs; } ;
struct TYPE_9__ {TYPE_2__ run; TYPE_1__ para; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_3__ member; } ;
typedef  int /*<<< orphan*/  ME_TextEditor ;
typedef  TYPE_4__ ME_DisplayItem ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ diParagraph ; 
 scalar_t__ diRun ; 

int ME_CharOfsFromRunOfs(ME_TextEditor *editor, const ME_DisplayItem *pPara,
                         const ME_DisplayItem *pRun, int nOfs)
{
  assert(pRun && pRun->type == diRun);
  assert(pPara && pPara->type == diParagraph);
  return pPara->member.para.nCharOfs + pRun->member.run.nCharOfs + nOfs;
}