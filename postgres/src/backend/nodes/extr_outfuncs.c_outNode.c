#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  StringInfo ;

/* Variables and functions */
 int /*<<< orphan*/  BitString ; 
 int /*<<< orphan*/  Float ; 
 int /*<<< orphan*/  IntList ; 
 int /*<<< orphan*/  Integer ; 
 scalar_t__ IsA (void const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  List ; 
 int /*<<< orphan*/  OidList ; 
 int /*<<< orphan*/  String ; 
#define  T_A_ArrayExpr 339 
#define  T_A_Const 338 
#define  T_A_Expr 337 
#define  T_A_Indices 336 
#define  T_A_Indirection 335 
#define  T_A_Star 334 
#define  T_Agg 333 
#define  T_AggPath 332 
#define  T_Aggref 331 
#define  T_Alias 330 
#define  T_AlterStatsStmt 329 
#define  T_AlternativeSubPlan 328 
#define  T_Append 327 
#define  T_AppendPath 326 
#define  T_AppendRelInfo 325 
#define  T_ArrayCoerceExpr 324 
#define  T_ArrayExpr 323 
#define  T_BitmapAnd 322 
#define  T_BitmapAndPath 321 
#define  T_BitmapHeapPath 320 
#define  T_BitmapHeapScan 319 
#define  T_BitmapIndexScan 318 
#define  T_BitmapOr 317 
#define  T_BitmapOrPath 316 
#define  T_BoolExpr 315 
#define  T_BooleanTest 314 
#define  T_CaseExpr 313 
#define  T_CaseTestExpr 312 
#define  T_CaseWhen 311 
#define  T_CoalesceExpr 310 
#define  T_CoerceToDomain 309 
#define  T_CoerceToDomainValue 308 
#define  T_CoerceViaIO 307 
#define  T_CollateClause 306 
#define  T_CollateExpr 305 
#define  T_ColumnDef 304 
#define  T_ColumnRef 303 
#define  T_CommonTableExpr 302 
#define  T_Const 301 
#define  T_Constraint 300 
#define  T_ConvertRowtypeExpr 299 
#define  T_CreateForeignTableStmt 298 
#define  T_CreateStatsStmt 297 
#define  T_CreateStmt 296 
#define  T_CteScan 295 
#define  T_CurrentOfExpr 294 
#define  T_CustomPath 293 
#define  T_CustomScan 292 
#define  T_DeclareCursorStmt 291 
#define  T_DefElem 290 
#define  T_DistinctExpr 289 
#define  T_EquivalenceClass 288 
#define  T_EquivalenceMember 287 
#define  T_ExtensibleNode 286 
#define  T_FieldSelect 285 
#define  T_FieldStore 284 
#define  T_ForeignKeyCacheInfo 283 
#define  T_ForeignKeyOptInfo 282 
#define  T_ForeignPath 281 
#define  T_ForeignScan 280 
#define  T_FromExpr 279 
#define  T_FuncCall 278 
#define  T_FuncExpr 277 
#define  T_FunctionScan 276 
#define  T_Gather 275 
#define  T_GatherMerge 274 
#define  T_GatherMergePath 273 
#define  T_GatherPath 272 
#define  T_Group 271 
#define  T_GroupPath 270 
#define  T_GroupResultPath 269 
#define  T_GroupingFunc 268 
#define  T_GroupingSet 267 
#define  T_GroupingSetData 266 
#define  T_GroupingSetsPath 265 
#define  T_Hash 264 
#define  T_HashJoin 263 
#define  T_HashPath 262 
#define  T_ImportForeignSchemaStmt 261 
#define  T_IndexClause 260 
#define  T_IndexElem 259 
#define  T_IndexOnlyScan 258 
#define  T_IndexOptInfo 257 
#define  T_IndexPath 256 
#define  T_IndexScan 255 
#define  T_IndexStmt 254 
#define  T_InferenceElem 253 
#define  T_IntoClause 252 
#define  T_Join 251 
#define  T_JoinExpr 250 
#define  T_Limit 249 
#define  T_LimitPath 248 
#define  T_LockRows 247 
#define  T_LockRowsPath 246 
#define  T_LockingClause 245 
#define  T_Material 244 
#define  T_MaterialPath 243 
#define  T_MergeAppend 242 
#define  T_MergeAppendPath 241 
#define  T_MergeJoin 240 
#define  T_MergePath 239 
#define  T_MinMaxAggInfo 238 
#define  T_MinMaxAggPath 237 
#define  T_MinMaxExpr 236 
#define  T_ModifyTable 235 
#define  T_ModifyTablePath 234 
#define  T_MultiAssignRef 233 
#define  T_NamedArgExpr 232 
#define  T_NamedTuplestoreScan 231 
#define  T_NestLoop 230 
#define  T_NestLoopParam 229 
#define  T_NestPath 228 
#define  T_NextValueExpr 227 
#define  T_NotifyStmt 226 
#define  T_NullIfExpr 225 
#define  T_NullTest 224 
#define  T_OnConflictExpr 223 
#define  T_OpExpr 222 
#define  T_Param 221 
#define  T_ParamPathInfo 220 
#define  T_ParamRef 219 
#define  T_PartitionBoundSpec 218 
#define  T_PartitionElem 217 
#define  T_PartitionPruneInfo 216 
#define  T_PartitionPruneStepCombine 215 
#define  T_PartitionPruneStepOp 214 
#define  T_PartitionRangeDatum 213 
#define  T_PartitionSpec 212 
#define  T_PartitionedRelPruneInfo 211 
#define  T_Path 210 
#define  T_PathKey 209 
#define  T_PathTarget 208 
#define  T_PlaceHolderInfo 207 
#define  T_PlaceHolderVar 206 
#define  T_Plan 205 
#define  T_PlanInvalItem 204 
#define  T_PlanRowMark 203 
#define  T_PlannedStmt 202 
#define  T_PlannerGlobal 201 
#define  T_PlannerInfo 200 
#define  T_PlannerParamItem 199 
#define  T_ProjectSet 198 
#define  T_ProjectSetPath 197 
#define  T_ProjectionPath 196 
#define  T_Query 195 
#define  T_RangeFunction 194 
#define  T_RangeSubselect 193 
#define  T_RangeTableFunc 192 
#define  T_RangeTableFuncCol 191 
#define  T_RangeTableSample 190 
#define  T_RangeTblEntry 189 
#define  T_RangeTblFunction 188 
#define  T_RangeTblRef 187 
#define  T_RangeVar 186 
#define  T_RawStmt 185 
#define  T_RecursiveUnion 184 
#define  T_RecursiveUnionPath 183 
#define  T_RelOptInfo 182 
#define  T_RelabelType 181 
#define  T_ResTarget 180 
#define  T_RestrictInfo 179 
#define  T_Result 178 
#define  T_RollupData 177 
#define  T_RowCompareExpr 176 
#define  T_RowExpr 175 
#define  T_RowMarkClause 174 
#define  T_SQLValueFunction 173 
#define  T_SampleScan 172 
#define  T_ScalarArrayOpExpr 171 
#define  T_Scan 170 
#define  T_SelectStmt 169 
#define  T_SeqScan 168 
#define  T_SetOp 167 
#define  T_SetOpPath 166 
#define  T_SetOperationStmt 165 
#define  T_SetToDefault 164 
#define  T_Sort 163 
#define  T_SortBy 162 
#define  T_SortGroupClause 161 
#define  T_SortPath 160 
#define  T_SpecialJoinInfo 159 
#define  T_StatisticExtInfo 158 
#define  T_SubLink 157 
#define  T_SubPlan 156 
#define  T_SubqueryScan 155 
#define  T_SubqueryScanPath 154 
#define  T_SubscriptingRef 153 
#define  T_TableFunc 152 
#define  T_TableFuncScan 151 
#define  T_TableLikeClause 150 
#define  T_TableSampleClause 149 
#define  T_TargetEntry 148 
#define  T_TidPath 147 
#define  T_TidScan 146 
#define  T_TriggerTransition 145 
#define  T_TypeCast 144 
#define  T_TypeName 143 
#define  T_Unique 142 
#define  T_UniquePath 141 
#define  T_UpperUniquePath 140 
#define  T_ValuesScan 139 
#define  T_Var 138 
#define  T_WindowAgg 137 
#define  T_WindowAggPath 136 
#define  T_WindowClause 135 
#define  T_WindowDef 134 
#define  T_WindowFunc 133 
#define  T_WithCheckOption 132 
#define  T_WithClause 131 
#define  T_WorkTableScan 130 
#define  T_XmlExpr 129 
#define  T_XmlSerialize 128 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  _outAConst (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outA_ArrayExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outA_Indices (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outA_Indirection (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outA_Star (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAgg (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAggPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAggref (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAlias (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAlterStatsStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAlternativeSubPlan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAppend (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAppendPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outAppendRelInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outArrayCoerceExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outArrayExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBitmapAnd (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBitmapAndPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBitmapHeapPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBitmapHeapScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBitmapIndexScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBitmapOr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBitmapOrPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBoolExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outBooleanTest (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCaseExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCaseTestExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCaseWhen (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCoalesceExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCoerceToDomain (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCoerceToDomainValue (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCoerceViaIO (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCollateClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCollateExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outColumnDef (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outColumnRef (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCommonTableExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outConst (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outConstraint (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outConvertRowtypeExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCreateForeignTableStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCreateStatsStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCreateStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCteScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCurrentOfExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCustomPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outCustomScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outDeclareCursorStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outDefElem (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outDistinctExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outEquivalenceClass (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outEquivalenceMember (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outExtensibleNode (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outFieldSelect (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outFieldStore (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outForeignKeyCacheInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outForeignKeyOptInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outForeignPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outForeignScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outFromExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outFuncCall (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outFuncExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outFunctionScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGather (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGatherMerge (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGatherMergePath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGatherPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGroup (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGroupPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGroupResultPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGroupingFunc (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGroupingSet (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGroupingSetData (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outGroupingSetsPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outHash (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outHashJoin (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outHashPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outImportForeignSchemaStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIndexClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIndexElem (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIndexOnlyScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIndexOptInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIndexPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIndexScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIndexStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outInferenceElem (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outIntoClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outJoin (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outJoinExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outLimit (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outLimitPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outList (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outLockRows (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outLockRowsPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outLockingClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMaterial (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMaterialPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMergeAppend (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMergeAppendPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMergeJoin (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMergePath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMinMaxAggInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMinMaxAggPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMinMaxExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outModifyTable (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outModifyTablePath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outMultiAssignRef (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNamedArgExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNamedTuplestoreScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNestLoop (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNestLoopParam (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNestPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNextValueExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNotifyStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNullIfExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outNullTest (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outOnConflictExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outOpExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outParam (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outParamPathInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outParamRef (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionBoundSpec (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionElem (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionPruneInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionPruneStepCombine (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionPruneStepOp (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionRangeDatum (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionSpec (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPartitionedRelPruneInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPathKey (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPathTarget (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlaceHolderInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlaceHolderVar (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlanInvalItem (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlanRowMark (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlannedStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlannerGlobal (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlannerInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outPlannerParamItem (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outProjectSet (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outProjectSetPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outProjectionPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outQuery (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeFunction (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeSubselect (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeTableFunc (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeTableFuncCol (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeTableSample (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeTblEntry (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeTblFunction (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeTblRef (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRangeVar (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRawStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRecursiveUnion (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRecursiveUnionPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRelOptInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRelabelType (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outResTarget (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRestrictInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outResult (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRollupData (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRowCompareExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRowExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outRowMarkClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSQLValueFunction (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSampleScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outScalarArrayOpExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSelectStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSeqScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSetOp (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSetOpPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSetOperationStmt (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSetToDefault (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSort (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSortBy (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSortGroupClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSortPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSpecialJoinInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outStatisticExtInfo (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSubLink (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSubPlan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSubqueryScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSubqueryScanPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outSubscriptingRef (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTableFunc (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTableFuncScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTableLikeClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTableSampleClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTargetEntry (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTidPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTidScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTriggerTransition (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTypeCast (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outTypeName (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outUnique (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outUniquePath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outUpperUniquePath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outValue (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outValuesScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outVar (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWindowAgg (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWindowAggPath (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWindowClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWindowDef (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWindowFunc (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWithCheckOption (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWithClause (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outWorkTableScan (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outXmlExpr (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  _outXmlSerialize (int /*<<< orphan*/ ,void const*) ; 
 int /*<<< orphan*/  appendStringInfoChar (int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  appendStringInfoString (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_stack_depth () ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int nodeTag (void const*) ; 

void
outNode(StringInfo str, const void *obj)
{
	/* Guard against stack overflow due to overly complex expressions */
	check_stack_depth();

	if (obj == NULL)
		appendStringInfoString(str, "<>");
	else if (IsA(obj, List) ||IsA(obj, IntList) || IsA(obj, OidList))
		_outList(str, obj);
	else if (IsA(obj, Integer) ||
			 IsA(obj, Float) ||
			 IsA(obj, String) ||
			 IsA(obj, BitString))
	{
		/* nodeRead does not want to see { } around these! */
		_outValue(str, obj);
	}
	else
	{
		appendStringInfoChar(str, '{');
		switch (nodeTag(obj))
		{
			case T_PlannedStmt:
				_outPlannedStmt(str, obj);
				break;
			case T_Plan:
				_outPlan(str, obj);
				break;
			case T_Result:
				_outResult(str, obj);
				break;
			case T_ProjectSet:
				_outProjectSet(str, obj);
				break;
			case T_ModifyTable:
				_outModifyTable(str, obj);
				break;
			case T_Append:
				_outAppend(str, obj);
				break;
			case T_MergeAppend:
				_outMergeAppend(str, obj);
				break;
			case T_RecursiveUnion:
				_outRecursiveUnion(str, obj);
				break;
			case T_BitmapAnd:
				_outBitmapAnd(str, obj);
				break;
			case T_BitmapOr:
				_outBitmapOr(str, obj);
				break;
			case T_Gather:
				_outGather(str, obj);
				break;
			case T_GatherMerge:
				_outGatherMerge(str, obj);
				break;
			case T_Scan:
				_outScan(str, obj);
				break;
			case T_SeqScan:
				_outSeqScan(str, obj);
				break;
			case T_SampleScan:
				_outSampleScan(str, obj);
				break;
			case T_IndexScan:
				_outIndexScan(str, obj);
				break;
			case T_IndexOnlyScan:
				_outIndexOnlyScan(str, obj);
				break;
			case T_BitmapIndexScan:
				_outBitmapIndexScan(str, obj);
				break;
			case T_BitmapHeapScan:
				_outBitmapHeapScan(str, obj);
				break;
			case T_TidScan:
				_outTidScan(str, obj);
				break;
			case T_SubqueryScan:
				_outSubqueryScan(str, obj);
				break;
			case T_FunctionScan:
				_outFunctionScan(str, obj);
				break;
			case T_TableFuncScan:
				_outTableFuncScan(str, obj);
				break;
			case T_ValuesScan:
				_outValuesScan(str, obj);
				break;
			case T_CteScan:
				_outCteScan(str, obj);
				break;
			case T_NamedTuplestoreScan:
				_outNamedTuplestoreScan(str, obj);
				break;
			case T_WorkTableScan:
				_outWorkTableScan(str, obj);
				break;
			case T_ForeignScan:
				_outForeignScan(str, obj);
				break;
			case T_CustomScan:
				_outCustomScan(str, obj);
				break;
			case T_Join:
				_outJoin(str, obj);
				break;
			case T_NestLoop:
				_outNestLoop(str, obj);
				break;
			case T_MergeJoin:
				_outMergeJoin(str, obj);
				break;
			case T_HashJoin:
				_outHashJoin(str, obj);
				break;
			case T_Agg:
				_outAgg(str, obj);
				break;
			case T_WindowAgg:
				_outWindowAgg(str, obj);
				break;
			case T_Group:
				_outGroup(str, obj);
				break;
			case T_Material:
				_outMaterial(str, obj);
				break;
			case T_Sort:
				_outSort(str, obj);
				break;
			case T_Unique:
				_outUnique(str, obj);
				break;
			case T_Hash:
				_outHash(str, obj);
				break;
			case T_SetOp:
				_outSetOp(str, obj);
				break;
			case T_LockRows:
				_outLockRows(str, obj);
				break;
			case T_Limit:
				_outLimit(str, obj);
				break;
			case T_NestLoopParam:
				_outNestLoopParam(str, obj);
				break;
			case T_PlanRowMark:
				_outPlanRowMark(str, obj);
				break;
			case T_PartitionPruneInfo:
				_outPartitionPruneInfo(str, obj);
				break;
			case T_PartitionedRelPruneInfo:
				_outPartitionedRelPruneInfo(str, obj);
				break;
			case T_PartitionPruneStepOp:
				_outPartitionPruneStepOp(str, obj);
				break;
			case T_PartitionPruneStepCombine:
				_outPartitionPruneStepCombine(str, obj);
				break;
			case T_PlanInvalItem:
				_outPlanInvalItem(str, obj);
				break;
			case T_Alias:
				_outAlias(str, obj);
				break;
			case T_RangeVar:
				_outRangeVar(str, obj);
				break;
			case T_TableFunc:
				_outTableFunc(str, obj);
				break;
			case T_IntoClause:
				_outIntoClause(str, obj);
				break;
			case T_Var:
				_outVar(str, obj);
				break;
			case T_Const:
				_outConst(str, obj);
				break;
			case T_Param:
				_outParam(str, obj);
				break;
			case T_Aggref:
				_outAggref(str, obj);
				break;
			case T_GroupingFunc:
				_outGroupingFunc(str, obj);
				break;
			case T_WindowFunc:
				_outWindowFunc(str, obj);
				break;
			case T_SubscriptingRef:
				_outSubscriptingRef(str, obj);
				break;
			case T_FuncExpr:
				_outFuncExpr(str, obj);
				break;
			case T_NamedArgExpr:
				_outNamedArgExpr(str, obj);
				break;
			case T_OpExpr:
				_outOpExpr(str, obj);
				break;
			case T_DistinctExpr:
				_outDistinctExpr(str, obj);
				break;
			case T_NullIfExpr:
				_outNullIfExpr(str, obj);
				break;
			case T_ScalarArrayOpExpr:
				_outScalarArrayOpExpr(str, obj);
				break;
			case T_BoolExpr:
				_outBoolExpr(str, obj);
				break;
			case T_SubLink:
				_outSubLink(str, obj);
				break;
			case T_SubPlan:
				_outSubPlan(str, obj);
				break;
			case T_AlternativeSubPlan:
				_outAlternativeSubPlan(str, obj);
				break;
			case T_FieldSelect:
				_outFieldSelect(str, obj);
				break;
			case T_FieldStore:
				_outFieldStore(str, obj);
				break;
			case T_RelabelType:
				_outRelabelType(str, obj);
				break;
			case T_CoerceViaIO:
				_outCoerceViaIO(str, obj);
				break;
			case T_ArrayCoerceExpr:
				_outArrayCoerceExpr(str, obj);
				break;
			case T_ConvertRowtypeExpr:
				_outConvertRowtypeExpr(str, obj);
				break;
			case T_CollateExpr:
				_outCollateExpr(str, obj);
				break;
			case T_CaseExpr:
				_outCaseExpr(str, obj);
				break;
			case T_CaseWhen:
				_outCaseWhen(str, obj);
				break;
			case T_CaseTestExpr:
				_outCaseTestExpr(str, obj);
				break;
			case T_ArrayExpr:
				_outArrayExpr(str, obj);
				break;
			case T_RowExpr:
				_outRowExpr(str, obj);
				break;
			case T_RowCompareExpr:
				_outRowCompareExpr(str, obj);
				break;
			case T_CoalesceExpr:
				_outCoalesceExpr(str, obj);
				break;
			case T_MinMaxExpr:
				_outMinMaxExpr(str, obj);
				break;
			case T_SQLValueFunction:
				_outSQLValueFunction(str, obj);
				break;
			case T_XmlExpr:
				_outXmlExpr(str, obj);
				break;
			case T_NullTest:
				_outNullTest(str, obj);
				break;
			case T_BooleanTest:
				_outBooleanTest(str, obj);
				break;
			case T_CoerceToDomain:
				_outCoerceToDomain(str, obj);
				break;
			case T_CoerceToDomainValue:
				_outCoerceToDomainValue(str, obj);
				break;
			case T_SetToDefault:
				_outSetToDefault(str, obj);
				break;
			case T_CurrentOfExpr:
				_outCurrentOfExpr(str, obj);
				break;
			case T_NextValueExpr:
				_outNextValueExpr(str, obj);
				break;
			case T_InferenceElem:
				_outInferenceElem(str, obj);
				break;
			case T_TargetEntry:
				_outTargetEntry(str, obj);
				break;
			case T_RangeTblRef:
				_outRangeTblRef(str, obj);
				break;
			case T_JoinExpr:
				_outJoinExpr(str, obj);
				break;
			case T_FromExpr:
				_outFromExpr(str, obj);
				break;
			case T_OnConflictExpr:
				_outOnConflictExpr(str, obj);
				break;
			case T_Path:
				_outPath(str, obj);
				break;
			case T_IndexPath:
				_outIndexPath(str, obj);
				break;
			case T_BitmapHeapPath:
				_outBitmapHeapPath(str, obj);
				break;
			case T_BitmapAndPath:
				_outBitmapAndPath(str, obj);
				break;
			case T_BitmapOrPath:
				_outBitmapOrPath(str, obj);
				break;
			case T_TidPath:
				_outTidPath(str, obj);
				break;
			case T_SubqueryScanPath:
				_outSubqueryScanPath(str, obj);
				break;
			case T_ForeignPath:
				_outForeignPath(str, obj);
				break;
			case T_CustomPath:
				_outCustomPath(str, obj);
				break;
			case T_AppendPath:
				_outAppendPath(str, obj);
				break;
			case T_MergeAppendPath:
				_outMergeAppendPath(str, obj);
				break;
			case T_GroupResultPath:
				_outGroupResultPath(str, obj);
				break;
			case T_MaterialPath:
				_outMaterialPath(str, obj);
				break;
			case T_UniquePath:
				_outUniquePath(str, obj);
				break;
			case T_GatherPath:
				_outGatherPath(str, obj);
				break;
			case T_ProjectionPath:
				_outProjectionPath(str, obj);
				break;
			case T_ProjectSetPath:
				_outProjectSetPath(str, obj);
				break;
			case T_SortPath:
				_outSortPath(str, obj);
				break;
			case T_GroupPath:
				_outGroupPath(str, obj);
				break;
			case T_UpperUniquePath:
				_outUpperUniquePath(str, obj);
				break;
			case T_AggPath:
				_outAggPath(str, obj);
				break;
			case T_GroupingSetsPath:
				_outGroupingSetsPath(str, obj);
				break;
			case T_MinMaxAggPath:
				_outMinMaxAggPath(str, obj);
				break;
			case T_WindowAggPath:
				_outWindowAggPath(str, obj);
				break;
			case T_SetOpPath:
				_outSetOpPath(str, obj);
				break;
			case T_RecursiveUnionPath:
				_outRecursiveUnionPath(str, obj);
				break;
			case T_LockRowsPath:
				_outLockRowsPath(str, obj);
				break;
			case T_ModifyTablePath:
				_outModifyTablePath(str, obj);
				break;
			case T_LimitPath:
				_outLimitPath(str, obj);
				break;
			case T_GatherMergePath:
				_outGatherMergePath(str, obj);
				break;
			case T_NestPath:
				_outNestPath(str, obj);
				break;
			case T_MergePath:
				_outMergePath(str, obj);
				break;
			case T_HashPath:
				_outHashPath(str, obj);
				break;
			case T_PlannerGlobal:
				_outPlannerGlobal(str, obj);
				break;
			case T_PlannerInfo:
				_outPlannerInfo(str, obj);
				break;
			case T_RelOptInfo:
				_outRelOptInfo(str, obj);
				break;
			case T_IndexOptInfo:
				_outIndexOptInfo(str, obj);
				break;
			case T_ForeignKeyOptInfo:
				_outForeignKeyOptInfo(str, obj);
				break;
			case T_EquivalenceClass:
				_outEquivalenceClass(str, obj);
				break;
			case T_EquivalenceMember:
				_outEquivalenceMember(str, obj);
				break;
			case T_PathKey:
				_outPathKey(str, obj);
				break;
			case T_PathTarget:
				_outPathTarget(str, obj);
				break;
			case T_ParamPathInfo:
				_outParamPathInfo(str, obj);
				break;
			case T_RestrictInfo:
				_outRestrictInfo(str, obj);
				break;
			case T_IndexClause:
				_outIndexClause(str, obj);
				break;
			case T_PlaceHolderVar:
				_outPlaceHolderVar(str, obj);
				break;
			case T_SpecialJoinInfo:
				_outSpecialJoinInfo(str, obj);
				break;
			case T_AppendRelInfo:
				_outAppendRelInfo(str, obj);
				break;
			case T_PlaceHolderInfo:
				_outPlaceHolderInfo(str, obj);
				break;
			case T_MinMaxAggInfo:
				_outMinMaxAggInfo(str, obj);
				break;
			case T_PlannerParamItem:
				_outPlannerParamItem(str, obj);
				break;
			case T_RollupData:
				_outRollupData(str, obj);
				break;
			case T_GroupingSetData:
				_outGroupingSetData(str, obj);
				break;
			case T_StatisticExtInfo:
				_outStatisticExtInfo(str, obj);
				break;
			case T_ExtensibleNode:
				_outExtensibleNode(str, obj);
				break;
			case T_CreateStmt:
				_outCreateStmt(str, obj);
				break;
			case T_CreateForeignTableStmt:
				_outCreateForeignTableStmt(str, obj);
				break;
			case T_ImportForeignSchemaStmt:
				_outImportForeignSchemaStmt(str, obj);
				break;
			case T_IndexStmt:
				_outIndexStmt(str, obj);
				break;
			case T_CreateStatsStmt:
				_outCreateStatsStmt(str, obj);
				break;
			case T_AlterStatsStmt:
				_outAlterStatsStmt(str, obj);
				break;
			case T_NotifyStmt:
				_outNotifyStmt(str, obj);
				break;
			case T_DeclareCursorStmt:
				_outDeclareCursorStmt(str, obj);
				break;
			case T_SelectStmt:
				_outSelectStmt(str, obj);
				break;
			case T_ColumnDef:
				_outColumnDef(str, obj);
				break;
			case T_TypeName:
				_outTypeName(str, obj);
				break;
			case T_TypeCast:
				_outTypeCast(str, obj);
				break;
			case T_CollateClause:
				_outCollateClause(str, obj);
				break;
			case T_IndexElem:
				_outIndexElem(str, obj);
				break;
			case T_Query:
				_outQuery(str, obj);
				break;
			case T_WithCheckOption:
				_outWithCheckOption(str, obj);
				break;
			case T_SortGroupClause:
				_outSortGroupClause(str, obj);
				break;
			case T_GroupingSet:
				_outGroupingSet(str, obj);
				break;
			case T_WindowClause:
				_outWindowClause(str, obj);
				break;
			case T_RowMarkClause:
				_outRowMarkClause(str, obj);
				break;
			case T_WithClause:
				_outWithClause(str, obj);
				break;
			case T_CommonTableExpr:
				_outCommonTableExpr(str, obj);
				break;
			case T_SetOperationStmt:
				_outSetOperationStmt(str, obj);
				break;
			case T_RangeTblEntry:
				_outRangeTblEntry(str, obj);
				break;
			case T_RangeTblFunction:
				_outRangeTblFunction(str, obj);
				break;
			case T_TableSampleClause:
				_outTableSampleClause(str, obj);
				break;
			case T_A_Expr:
				_outAExpr(str, obj);
				break;
			case T_ColumnRef:
				_outColumnRef(str, obj);
				break;
			case T_ParamRef:
				_outParamRef(str, obj);
				break;
			case T_RawStmt:
				_outRawStmt(str, obj);
				break;
			case T_A_Const:
				_outAConst(str, obj);
				break;
			case T_A_Star:
				_outA_Star(str, obj);
				break;
			case T_A_Indices:
				_outA_Indices(str, obj);
				break;
			case T_A_Indirection:
				_outA_Indirection(str, obj);
				break;
			case T_A_ArrayExpr:
				_outA_ArrayExpr(str, obj);
				break;
			case T_ResTarget:
				_outResTarget(str, obj);
				break;
			case T_MultiAssignRef:
				_outMultiAssignRef(str, obj);
				break;
			case T_SortBy:
				_outSortBy(str, obj);
				break;
			case T_WindowDef:
				_outWindowDef(str, obj);
				break;
			case T_RangeSubselect:
				_outRangeSubselect(str, obj);
				break;
			case T_RangeFunction:
				_outRangeFunction(str, obj);
				break;
			case T_RangeTableSample:
				_outRangeTableSample(str, obj);
				break;
			case T_RangeTableFunc:
				_outRangeTableFunc(str, obj);
				break;
			case T_RangeTableFuncCol:
				_outRangeTableFuncCol(str, obj);
				break;
			case T_Constraint:
				_outConstraint(str, obj);
				break;
			case T_FuncCall:
				_outFuncCall(str, obj);
				break;
			case T_DefElem:
				_outDefElem(str, obj);
				break;
			case T_TableLikeClause:
				_outTableLikeClause(str, obj);
				break;
			case T_LockingClause:
				_outLockingClause(str, obj);
				break;
			case T_XmlSerialize:
				_outXmlSerialize(str, obj);
				break;
			case T_ForeignKeyCacheInfo:
				_outForeignKeyCacheInfo(str, obj);
				break;
			case T_TriggerTransition:
				_outTriggerTransition(str, obj);
				break;
			case T_PartitionElem:
				_outPartitionElem(str, obj);
				break;
			case T_PartitionSpec:
				_outPartitionSpec(str, obj);
				break;
			case T_PartitionBoundSpec:
				_outPartitionBoundSpec(str, obj);
				break;
			case T_PartitionRangeDatum:
				_outPartitionRangeDatum(str, obj);
				break;

			default:

				/*
				 * This should be an ERROR, but it's too useful to be able to
				 * dump structures that outNode only understands part of.
				 */
				elog(WARNING, "could not dump unrecognized node type: %d",
					 (int) nodeTag(obj));
				break;
		}
		appendStringInfoChar(str, '}');
	}
}