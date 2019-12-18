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
typedef  int /*<<< orphan*/  Node ;

/* Variables and functions */
 int /*<<< orphan*/  CreateCommandTag (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsInParallelMode () ; 
 int /*<<< orphan*/  PreventCommandIfParallelMode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PreventCommandIfReadOnly (int /*<<< orphan*/ ) ; 
#define  T_AlterDatabaseSetStmt 201 
#define  T_AlterDatabaseStmt 200 
#define  T_AlterDefaultPrivilegesStmt 199 
#define  T_AlterDomainStmt 198 
#define  T_AlterEnumStmt 197 
#define  T_AlterEventTrigStmt 196 
#define  T_AlterExtensionContentsStmt 195 
#define  T_AlterExtensionStmt 194 
#define  T_AlterFdwStmt 193 
#define  T_AlterForeignServerStmt 192 
#define  T_AlterFunctionStmt 191 
#define  T_AlterObjectDependsStmt 190 
#define  T_AlterObjectSchemaStmt 189 
#define  T_AlterOpFamilyStmt 188 
#define  T_AlterOperatorStmt 187 
#define  T_AlterOwnerStmt 186 
#define  T_AlterPublicationStmt 185 
#define  T_AlterRoleSetStmt 184 
#define  T_AlterRoleStmt 183 
#define  T_AlterSeqStmt 182 
#define  T_AlterSubscriptionStmt 181 
#define  T_AlterTSConfigurationStmt 180 
#define  T_AlterTSDictionaryStmt 179 
#define  T_AlterTableMoveAllStmt 178 
#define  T_AlterTableSpaceOptionsStmt 177 
#define  T_AlterTableStmt 176 
#define  T_AlterUserMappingStmt 175 
#define  T_CommentStmt 174 
#define  T_CompositeTypeStmt 173 
#define  T_CreateCastStmt 172 
#define  T_CreateConversionStmt 171 
#define  T_CreateDomainStmt 170 
#define  T_CreateEnumStmt 169 
#define  T_CreateEventTrigStmt 168 
#define  T_CreateExtensionStmt 167 
#define  T_CreateFdwStmt 166 
#define  T_CreateForeignServerStmt 165 
#define  T_CreateForeignTableStmt 164 
#define  T_CreateFunctionStmt 163 
#define  T_CreateOpClassStmt 162 
#define  T_CreateOpFamilyStmt 161 
#define  T_CreatePLangStmt 160 
#define  T_CreatePublicationStmt 159 
#define  T_CreateRangeStmt 158 
#define  T_CreateRoleStmt 157 
#define  T_CreateSchemaStmt 156 
#define  T_CreateSeqStmt 155 
#define  T_CreateStmt 154 
#define  T_CreateSubscriptionStmt 153 
#define  T_CreateTableAsStmt 152 
#define  T_CreateTableSpaceStmt 151 
#define  T_CreateTransformStmt 150 
#define  T_CreateTrigStmt 149 
#define  T_CreateUserMappingStmt 148 
#define  T_CreatedbStmt 147 
#define  T_DefineStmt 146 
#define  T_DropOwnedStmt 145 
#define  T_DropRoleStmt 144 
#define  T_DropStmt 143 
#define  T_DropSubscriptionStmt 142 
#define  T_DropTableSpaceStmt 141 
#define  T_DropUserMappingStmt 140 
#define  T_DropdbStmt 139 
#define  T_GrantRoleStmt 138 
#define  T_GrantStmt 137 
#define  T_ImportForeignSchemaStmt 136 
#define  T_IndexStmt 135 
#define  T_ReassignOwnedStmt 134 
#define  T_RefreshMatViewStmt 133 
#define  T_RenameStmt 132 
#define  T_RuleStmt 131 
#define  T_SecLabelStmt 130 
#define  T_TruncateStmt 129 
#define  T_ViewStmt 128 
 int /*<<< orphan*/  XactReadOnly ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
check_xact_readonly(Node *parsetree)
{
	/* Only perform the check if we have a reason to do so. */
	if (!XactReadOnly && !IsInParallelMode())
		return;

	/*
	 * Note: Commands that need to do more complicated checking are handled
	 * elsewhere, in particular COPY and plannable statements do their own
	 * checking.  However they should all call PreventCommandIfReadOnly or
	 * PreventCommandIfParallelMode to actually throw the error.
	 */

	switch (nodeTag(parsetree))
	{
		case T_AlterDatabaseStmt:
		case T_AlterDatabaseSetStmt:
		case T_AlterDomainStmt:
		case T_AlterFunctionStmt:
		case T_AlterRoleStmt:
		case T_AlterRoleSetStmt:
		case T_AlterObjectDependsStmt:
		case T_AlterObjectSchemaStmt:
		case T_AlterOwnerStmt:
		case T_AlterOperatorStmt:
		case T_AlterSeqStmt:
		case T_AlterTableMoveAllStmt:
		case T_AlterTableStmt:
		case T_RenameStmt:
		case T_CommentStmt:
		case T_DefineStmt:
		case T_CreateCastStmt:
		case T_CreateEventTrigStmt:
		case T_AlterEventTrigStmt:
		case T_CreateConversionStmt:
		case T_CreatedbStmt:
		case T_CreateDomainStmt:
		case T_CreateFunctionStmt:
		case T_CreateRoleStmt:
		case T_IndexStmt:
		case T_CreatePLangStmt:
		case T_CreateOpClassStmt:
		case T_CreateOpFamilyStmt:
		case T_AlterOpFamilyStmt:
		case T_RuleStmt:
		case T_CreateSchemaStmt:
		case T_CreateSeqStmt:
		case T_CreateStmt:
		case T_CreateTableAsStmt:
		case T_RefreshMatViewStmt:
		case T_CreateTableSpaceStmt:
		case T_CreateTransformStmt:
		case T_CreateTrigStmt:
		case T_CompositeTypeStmt:
		case T_CreateEnumStmt:
		case T_CreateRangeStmt:
		case T_AlterEnumStmt:
		case T_ViewStmt:
		case T_DropStmt:
		case T_DropdbStmt:
		case T_DropTableSpaceStmt:
		case T_DropRoleStmt:
		case T_GrantStmt:
		case T_GrantRoleStmt:
		case T_AlterDefaultPrivilegesStmt:
		case T_TruncateStmt:
		case T_DropOwnedStmt:
		case T_ReassignOwnedStmt:
		case T_AlterTSDictionaryStmt:
		case T_AlterTSConfigurationStmt:
		case T_CreateExtensionStmt:
		case T_AlterExtensionStmt:
		case T_AlterExtensionContentsStmt:
		case T_CreateFdwStmt:
		case T_AlterFdwStmt:
		case T_CreateForeignServerStmt:
		case T_AlterForeignServerStmt:
		case T_CreateUserMappingStmt:
		case T_AlterUserMappingStmt:
		case T_DropUserMappingStmt:
		case T_AlterTableSpaceOptionsStmt:
		case T_CreateForeignTableStmt:
		case T_ImportForeignSchemaStmt:
		case T_SecLabelStmt:
		case T_CreatePublicationStmt:
		case T_AlterPublicationStmt:
		case T_CreateSubscriptionStmt:
		case T_AlterSubscriptionStmt:
		case T_DropSubscriptionStmt:
			PreventCommandIfReadOnly(CreateCommandTag(parsetree));
			PreventCommandIfParallelMode(CreateCommandTag(parsetree));
			break;
		default:
			/* do nothing */
			break;
	}
}