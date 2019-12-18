#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int flags; int progLength; int /*<<< orphan*/  treeDepth; } ;
struct TYPE_17__ {int index; } ;
struct TYPE_16__ {int ch1; int ch2; } ;
struct TYPE_15__ {int chr; } ;
struct TYPE_18__ {TYPE_3__ ucclass; TYPE_6__* kid2; TYPE_2__ altprereq; TYPE_1__ flat; } ;
struct TYPE_20__ {struct TYPE_20__* next; TYPE_4__ u; struct TYPE_20__* kid; void* op; } ;
struct TYPE_19__ {int op; int /*<<< orphan*/  errPos; } ;
typedef  TYPE_5__ REOpData ;
typedef  TYPE_6__ RENode ;
typedef  int /*<<< orphan*/  INT ;
typedef  TYPE_7__ CompilerState ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JSMSG_MISSING_PAREN ; 
 int /*<<< orphan*/  JSMSG_REGEXP_TOO_COMPLEX ; 
 int /*<<< orphan*/  JSREPORT_ERROR ; 
 TYPE_6__* NewRENode (TYPE_7__*,int const) ; 
 int REG_FOLD ; 
#define  REOP_ALT 133 
 void* REOP_ALTPREREQ ; 
 void* REOP_ALTPREREQ2 ; 
#define  REOP_ASSERT 132 
#define  REOP_ASSERT_NOT 131 
 void* REOP_CLASS ; 
#define  REOP_CONCAT 130 
 void* REOP_FLAT ; 
#define  REOP_LPAREN 129 
#define  REOP_LPARENNON 128 
 int /*<<< orphan*/  ReportRegExpError (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReportRegExpErrorHelper (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_DEPTH_MAX ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
ProcessOp(CompilerState *state, REOpData *opData, RENode **operandStack,
          INT operandSP)
{
    RENode *result;

    switch (opData->op) {
      case REOP_ALT:
        result = NewRENode(state, REOP_ALT);
        if (!result)
            return FALSE;
        result->kid = operandStack[operandSP - 2];
        result->u.kid2 = operandStack[operandSP - 1];
        operandStack[operandSP - 2] = result;

        if (state->treeDepth == TREE_DEPTH_MAX) {
            ReportRegExpError(state, JSREPORT_ERROR, JSMSG_REGEXP_TOO_COMPLEX);
            return FALSE;
        }
        ++state->treeDepth;

        /*
         * Look at both alternates to see if there's a FLAT or a CLASS at
         * the start of each. If so, use a prerequisite match.
         */
        if (((RENode *) result->kid)->op == REOP_FLAT &&
            ((RENode *) result->u.kid2)->op == REOP_FLAT &&
            (state->flags & REG_FOLD) == 0) {
            result->op = REOP_ALTPREREQ;
            result->u.altprereq.ch1 = ((RENode *) result->kid)->u.flat.chr;
            result->u.altprereq.ch2 = ((RENode *) result->u.kid2)->u.flat.chr;
            /* ALTPREREQ, <end>, uch1, uch2, <next>, ...,
                                            JUMP, <end> ... ENDALT */
            state->progLength += 13;
        }
        else
        if (((RENode *) result->kid)->op == REOP_CLASS &&
            ((RENode *) result->kid)->u.ucclass.index < 256 &&
            ((RENode *) result->u.kid2)->op == REOP_FLAT &&
            (state->flags & REG_FOLD) == 0) {
            result->op = REOP_ALTPREREQ2;
            result->u.altprereq.ch1 = ((RENode *) result->u.kid2)->u.flat.chr;
            result->u.altprereq.ch2 = ((RENode *) result->kid)->u.ucclass.index;
            /* ALTPREREQ2, <end>, uch1, uch2, <next>, ...,
                                            JUMP, <end> ... ENDALT */
            state->progLength += 13;
        }
        else
        if (((RENode *) result->kid)->op == REOP_FLAT &&
            ((RENode *) result->u.kid2)->op == REOP_CLASS &&
            ((RENode *) result->u.kid2)->u.ucclass.index < 256 &&
            (state->flags & REG_FOLD) == 0) {
            result->op = REOP_ALTPREREQ2;
            result->u.altprereq.ch1 = ((RENode *) result->kid)->u.flat.chr;
            result->u.altprereq.ch2 =
                ((RENode *) result->u.kid2)->u.ucclass.index;
            /* ALTPREREQ2, <end>, uch1, uch2, <next>, ...,
                                          JUMP, <end> ... ENDALT */
            state->progLength += 13;
        }
        else {
            /* ALT, <next>, ..., JUMP, <end> ... ENDALT */
            state->progLength += 7;
        }
        break;

      case REOP_CONCAT:
        result = operandStack[operandSP - 2];
        while (result->next)
            result = result->next;
        result->next = operandStack[operandSP - 1];
        break;

      case REOP_ASSERT:
      case REOP_ASSERT_NOT:
      case REOP_LPARENNON:
      case REOP_LPAREN:
        /* These should have been processed by a close paren. */
        ReportRegExpErrorHelper(state, JSREPORT_ERROR, JSMSG_MISSING_PAREN,
                                opData->errPos);
        return FALSE;

      default:;
    }
    return TRUE;
}