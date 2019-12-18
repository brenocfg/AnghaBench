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
typedef  int /*<<< orphan*/  WorkTableScanState ;
typedef  int /*<<< orphan*/  WindowAggState ;
typedef  int /*<<< orphan*/  ValuesScanState ;
typedef  int /*<<< orphan*/  UniqueState ;
typedef  int /*<<< orphan*/  TidScanState ;
typedef  int /*<<< orphan*/  TableFuncScanState ;
struct TYPE_4__ {int /*<<< orphan*/ * chgParam; } ;
typedef  int /*<<< orphan*/  SubqueryScanState ;
typedef  int /*<<< orphan*/  SortState ;
typedef  int /*<<< orphan*/  SetOpState ;
typedef  int /*<<< orphan*/  SeqScanState ;
typedef  int /*<<< orphan*/  SampleScanState ;
typedef  int /*<<< orphan*/  ResultState ;
typedef  int /*<<< orphan*/  RecursiveUnionState ;
typedef  int /*<<< orphan*/  ProjectSetState ;
typedef  TYPE_1__ PlanState ;
typedef  int /*<<< orphan*/  NestLoopState ;
typedef  int /*<<< orphan*/  NamedTuplestoreScanState ;
typedef  int /*<<< orphan*/  ModifyTableState ;
typedef  int /*<<< orphan*/  MergeJoinState ;
typedef  int /*<<< orphan*/  MergeAppendState ;
typedef  int /*<<< orphan*/  MaterialState ;
typedef  int /*<<< orphan*/  LockRowsState ;
typedef  int /*<<< orphan*/  LimitState ;
typedef  int /*<<< orphan*/  IndexScanState ;
typedef  int /*<<< orphan*/  IndexOnlyScanState ;
typedef  int /*<<< orphan*/  HashState ;
typedef  int /*<<< orphan*/  HashJoinState ;
typedef  int /*<<< orphan*/  GroupState ;
typedef  int /*<<< orphan*/  GatherState ;
typedef  int /*<<< orphan*/  GatherMergeState ;
typedef  int /*<<< orphan*/  FunctionScanState ;
typedef  int /*<<< orphan*/  ForeignScanState ;
typedef  int /*<<< orphan*/  CustomScanState ;
typedef  int /*<<< orphan*/  CteScanState ;
typedef  int /*<<< orphan*/  BitmapOrState ;
typedef  int /*<<< orphan*/  BitmapIndexScanState ;
typedef  int /*<<< orphan*/  BitmapHeapScanState ;
typedef  int /*<<< orphan*/  BitmapAndState ;
typedef  int /*<<< orphan*/  AppendState ;
typedef  int /*<<< orphan*/  AggState ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  ExecEndAgg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndAppend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndBitmapAnd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndBitmapHeapScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndBitmapIndexScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndBitmapOr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndCteScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndCustomScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndForeignScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndFunctionScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndGather (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndGatherMerge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndGroup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndHash (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndHashJoin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndIndexOnlyScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndIndexScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndLimit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndLockRows (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndMaterial (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndMergeAppend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndMergeJoin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndModifyTable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndNamedTuplestoreScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndNestLoop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndProjectSet (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndRecursiveUnion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndResult (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndSampleScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndSeqScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndSetOp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndSort (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndSubqueryScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndTableFuncScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndTidScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndUnique (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndValuesScan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndWindowAgg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ExecEndWorkTableScan (int /*<<< orphan*/ *) ; 
#define  T_AggState 166 
#define  T_AppendState 165 
#define  T_BitmapAndState 164 
#define  T_BitmapHeapScanState 163 
#define  T_BitmapIndexScanState 162 
#define  T_BitmapOrState 161 
#define  T_CteScanState 160 
#define  T_CustomScanState 159 
#define  T_ForeignScanState 158 
#define  T_FunctionScanState 157 
#define  T_GatherMergeState 156 
#define  T_GatherState 155 
#define  T_GroupState 154 
#define  T_HashJoinState 153 
#define  T_HashState 152 
#define  T_IndexOnlyScanState 151 
#define  T_IndexScanState 150 
#define  T_LimitState 149 
#define  T_LockRowsState 148 
#define  T_MaterialState 147 
#define  T_MergeAppendState 146 
#define  T_MergeJoinState 145 
#define  T_ModifyTableState 144 
#define  T_NamedTuplestoreScanState 143 
#define  T_NestLoopState 142 
#define  T_ProjectSetState 141 
#define  T_RecursiveUnionState 140 
#define  T_ResultState 139 
#define  T_SampleScanState 138 
#define  T_SeqScanState 137 
#define  T_SetOpState 136 
#define  T_SortState 135 
#define  T_SubqueryScanState 134 
#define  T_TableFuncScanState 133 
#define  T_TidScanState 132 
#define  T_UniqueState 131 
#define  T_ValuesScanState 130 
#define  T_WindowAggState 129 
#define  T_WorkTableScanState 128 
 int /*<<< orphan*/  bms_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int nodeTag (TYPE_1__*) ; 

void
ExecEndNode(PlanState *node)
{
	/*
	 * do nothing when we get to the end of a leaf on tree.
	 */
	if (node == NULL)
		return;

	/*
	 * Make sure there's enough stack available. Need to check here, in
	 * addition to ExecProcNode() (via ExecProcNodeFirst()), because it's not
	 * guaranteed that ExecProcNode() is reached for all nodes.
	 */
	check_stack_depth();

	if (node->chgParam != NULL)
	{
		bms_free(node->chgParam);
		node->chgParam = NULL;
	}

	switch (nodeTag(node))
	{
			/*
			 * control nodes
			 */
		case T_ResultState:
			ExecEndResult((ResultState *) node);
			break;

		case T_ProjectSetState:
			ExecEndProjectSet((ProjectSetState *) node);
			break;

		case T_ModifyTableState:
			ExecEndModifyTable((ModifyTableState *) node);
			break;

		case T_AppendState:
			ExecEndAppend((AppendState *) node);
			break;

		case T_MergeAppendState:
			ExecEndMergeAppend((MergeAppendState *) node);
			break;

		case T_RecursiveUnionState:
			ExecEndRecursiveUnion((RecursiveUnionState *) node);
			break;

		case T_BitmapAndState:
			ExecEndBitmapAnd((BitmapAndState *) node);
			break;

		case T_BitmapOrState:
			ExecEndBitmapOr((BitmapOrState *) node);
			break;

			/*
			 * scan nodes
			 */
		case T_SeqScanState:
			ExecEndSeqScan((SeqScanState *) node);
			break;

		case T_SampleScanState:
			ExecEndSampleScan((SampleScanState *) node);
			break;

		case T_GatherState:
			ExecEndGather((GatherState *) node);
			break;

		case T_GatherMergeState:
			ExecEndGatherMerge((GatherMergeState *) node);
			break;

		case T_IndexScanState:
			ExecEndIndexScan((IndexScanState *) node);
			break;

		case T_IndexOnlyScanState:
			ExecEndIndexOnlyScan((IndexOnlyScanState *) node);
			break;

		case T_BitmapIndexScanState:
			ExecEndBitmapIndexScan((BitmapIndexScanState *) node);
			break;

		case T_BitmapHeapScanState:
			ExecEndBitmapHeapScan((BitmapHeapScanState *) node);
			break;

		case T_TidScanState:
			ExecEndTidScan((TidScanState *) node);
			break;

		case T_SubqueryScanState:
			ExecEndSubqueryScan((SubqueryScanState *) node);
			break;

		case T_FunctionScanState:
			ExecEndFunctionScan((FunctionScanState *) node);
			break;

		case T_TableFuncScanState:
			ExecEndTableFuncScan((TableFuncScanState *) node);
			break;

		case T_ValuesScanState:
			ExecEndValuesScan((ValuesScanState *) node);
			break;

		case T_CteScanState:
			ExecEndCteScan((CteScanState *) node);
			break;

		case T_NamedTuplestoreScanState:
			ExecEndNamedTuplestoreScan((NamedTuplestoreScanState *) node);
			break;

		case T_WorkTableScanState:
			ExecEndWorkTableScan((WorkTableScanState *) node);
			break;

		case T_ForeignScanState:
			ExecEndForeignScan((ForeignScanState *) node);
			break;

		case T_CustomScanState:
			ExecEndCustomScan((CustomScanState *) node);
			break;

			/*
			 * join nodes
			 */
		case T_NestLoopState:
			ExecEndNestLoop((NestLoopState *) node);
			break;

		case T_MergeJoinState:
			ExecEndMergeJoin((MergeJoinState *) node);
			break;

		case T_HashJoinState:
			ExecEndHashJoin((HashJoinState *) node);
			break;

			/*
			 * materialization nodes
			 */
		case T_MaterialState:
			ExecEndMaterial((MaterialState *) node);
			break;

		case T_SortState:
			ExecEndSort((SortState *) node);
			break;

		case T_GroupState:
			ExecEndGroup((GroupState *) node);
			break;

		case T_AggState:
			ExecEndAgg((AggState *) node);
			break;

		case T_WindowAggState:
			ExecEndWindowAgg((WindowAggState *) node);
			break;

		case T_UniqueState:
			ExecEndUnique((UniqueState *) node);
			break;

		case T_HashState:
			ExecEndHash((HashState *) node);
			break;

		case T_SetOpState:
			ExecEndSetOp((SetOpState *) node);
			break;

		case T_LockRowsState:
			ExecEndLockRows((LockRowsState *) node);
			break;

		case T_LimitState:
			ExecEndLimit((LimitState *) node);
			break;

		default:
			elog(ERROR, "unrecognized node type: %d", (int) nodeTag(node));
			break;
	}
}