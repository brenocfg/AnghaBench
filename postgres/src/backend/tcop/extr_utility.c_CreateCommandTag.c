#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_50__   TYPE_9__ ;
typedef  struct TYPE_49__   TYPE_8__ ;
typedef  struct TYPE_48__   TYPE_7__ ;
typedef  struct TYPE_47__   TYPE_6__ ;
typedef  struct TYPE_46__   TYPE_5__ ;
typedef  struct TYPE_45__   TYPE_4__ ;
typedef  struct TYPE_44__   TYPE_3__ ;
typedef  struct TYPE_43__   TYPE_2__ ;
typedef  struct TYPE_42__   TYPE_25__ ;
typedef  struct TYPE_41__   TYPE_24__ ;
typedef  struct TYPE_40__   TYPE_23__ ;
typedef  struct TYPE_39__   TYPE_22__ ;
typedef  struct TYPE_38__   TYPE_21__ ;
typedef  struct TYPE_37__   TYPE_20__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_19__ ;
typedef  struct TYPE_34__   TYPE_18__ ;
typedef  struct TYPE_33__   TYPE_17__ ;
typedef  struct TYPE_32__   TYPE_16__ ;
typedef  struct TYPE_31__   TYPE_15__ ;
typedef  struct TYPE_30__   TYPE_14__ ;
typedef  struct TYPE_29__   TYPE_13__ ;
typedef  struct TYPE_28__   TYPE_12__ ;
typedef  struct TYPE_27__   TYPE_11__ ;
typedef  struct TYPE_26__   TYPE_10__ ;

/* Type definitions */
struct TYPE_36__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_1__ VariableSetStmt ;
struct TYPE_43__ {int /*<<< orphan*/  is_vacuumcmd; } ;
typedef  TYPE_2__ VacuumStmt ;
struct TYPE_44__ {int /*<<< orphan*/  kind; } ;
typedef  TYPE_3__ TransactionStmt ;
struct TYPE_50__ {int /*<<< orphan*/  strength; } ;
struct TYPE_49__ {scalar_t__ commandType; int /*<<< orphan*/ * utilityStmt; int /*<<< orphan*/  rowMarks; } ;
struct TYPE_48__ {scalar_t__ commandType; int /*<<< orphan*/ * utilityStmt; int /*<<< orphan*/  rowMarks; } ;
struct TYPE_47__ {int /*<<< orphan*/ * stmt; } ;
struct TYPE_46__ {int /*<<< orphan*/  renameType; int /*<<< orphan*/  relationType; } ;
struct TYPE_45__ {int /*<<< orphan*/  strength; } ;
struct TYPE_42__ {int /*<<< orphan*/  objtype; } ;
struct TYPE_41__ {int /*<<< orphan*/  objectType; } ;
struct TYPE_40__ {int /*<<< orphan*/  objectType; } ;
struct TYPE_39__ {int /*<<< orphan*/  objectType; } ;
struct TYPE_38__ {int /*<<< orphan*/  objtype; } ;
struct TYPE_37__ {int /*<<< orphan*/  relkind; } ;
struct TYPE_35__ {int /*<<< orphan*/ * portalname; } ;
struct TYPE_34__ {int /*<<< orphan*/  is_procedure; } ;
struct TYPE_33__ {int /*<<< orphan*/  is_select_into; int /*<<< orphan*/  relkind; } ;
struct TYPE_32__ {int /*<<< orphan*/ * name; } ;
struct TYPE_31__ {int /*<<< orphan*/  kind; } ;
struct TYPE_30__ {int /*<<< orphan*/  target; } ;
struct TYPE_29__ {int /*<<< orphan*/  removeType; } ;
struct TYPE_28__ {int /*<<< orphan*/  ismove; } ;
struct TYPE_27__ {int /*<<< orphan*/  is_grant; } ;
struct TYPE_26__ {int /*<<< orphan*/  is_grant; } ;
typedef  TYPE_4__ RowMarkClause ;
typedef  TYPE_5__ RenameStmt ;
typedef  TYPE_6__ RawStmt ;
typedef  TYPE_7__ Query ;
typedef  TYPE_8__ PlannedStmt ;
typedef  TYPE_9__ PlanRowMark ;
typedef  int /*<<< orphan*/  Node ;
typedef  TYPE_10__ GrantStmt ;
typedef  TYPE_11__ GrantRoleStmt ;
typedef  TYPE_12__ FetchStmt ;
typedef  TYPE_13__ DropStmt ;
typedef  TYPE_14__ DiscardStmt ;
typedef  TYPE_15__ DefineStmt ;
typedef  TYPE_16__ DeallocateStmt ;
typedef  TYPE_17__ CreateTableAsStmt ;
typedef  TYPE_18__ CreateFunctionStmt ;
typedef  TYPE_19__ ClosePortalStmt ;
typedef  TYPE_20__ AlterTableStmt ;
typedef  TYPE_21__ AlterTableMoveAllStmt ;
typedef  TYPE_22__ AlterOwnerStmt ;
typedef  TYPE_23__ AlterObjectSchemaStmt ;
typedef  TYPE_24__ AlterObjectDependsStmt ;
typedef  TYPE_25__ AlterFunctionStmt ;

/* Variables and functions */
 char* AlterObjectTypeCommandTag (int /*<<< orphan*/ ) ; 
#define  CMD_DELETE 303 
#define  CMD_INSERT 302 
#define  CMD_SELECT 301 
#define  CMD_UPDATE 300 
#define  CMD_UTILITY 299 
#define  DISCARD_ALL 298 
#define  DISCARD_PLANS 297 
#define  DISCARD_SEQUENCES 296 
#define  DISCARD_TEMP 295 
#define  LCS_FORKEYSHARE 294 
#define  LCS_FORNOKEYUPDATE 293 
#define  LCS_FORSHARE 292 
#define  LCS_FORUPDATE 291 
 int /*<<< orphan*/  NIL ; 
#define  OBJECT_ACCESS_METHOD 290 
#define  OBJECT_AGGREGATE 289 
#define  OBJECT_CAST 288 
#define  OBJECT_COLLATION 287 
 int /*<<< orphan*/  OBJECT_COLUMN ; 
#define  OBJECT_CONVERSION 286 
#define  OBJECT_DOMAIN 285 
#define  OBJECT_EVENT_TRIGGER 284 
#define  OBJECT_EXTENSION 283 
#define  OBJECT_FDW 282 
#define  OBJECT_FOREIGN_SERVER 281 
#define  OBJECT_FOREIGN_TABLE 280 
#define  OBJECT_FUNCTION 279 
#define  OBJECT_INDEX 278 
#define  OBJECT_LANGUAGE 277 
#define  OBJECT_MATVIEW 276 
#define  OBJECT_OPCLASS 275 
#define  OBJECT_OPERATOR 274 
#define  OBJECT_OPFAMILY 273 
#define  OBJECT_POLICY 272 
#define  OBJECT_PROCEDURE 271 
#define  OBJECT_PUBLICATION 270 
#define  OBJECT_ROUTINE 269 
#define  OBJECT_RULE 268 
#define  OBJECT_SCHEMA 267 
#define  OBJECT_SEQUENCE 266 
#define  OBJECT_STATISTIC_EXT 265 
#define  OBJECT_TABLE 264 
#define  OBJECT_TRANSFORM 263 
#define  OBJECT_TRIGGER 262 
#define  OBJECT_TSCONFIGURATION 261 
#define  OBJECT_TSDICTIONARY 260 
#define  OBJECT_TSPARSER 259 
#define  OBJECT_TSTEMPLATE 258 
#define  OBJECT_TYPE 257 
#define  OBJECT_VIEW 256 
#define  TRANS_STMT_BEGIN 255 
#define  TRANS_STMT_COMMIT 254 
#define  TRANS_STMT_COMMIT_PREPARED 253 
#define  TRANS_STMT_PREPARE 252 
#define  TRANS_STMT_RELEASE 251 
#define  TRANS_STMT_ROLLBACK 250 
#define  TRANS_STMT_ROLLBACK_PREPARED 249 
#define  TRANS_STMT_ROLLBACK_TO 248 
#define  TRANS_STMT_SAVEPOINT 247 
#define  TRANS_STMT_START 246 
#define  T_AlterCollationStmt 245 
#define  T_AlterDatabaseSetStmt 244 
#define  T_AlterDatabaseStmt 243 
#define  T_AlterDefaultPrivilegesStmt 242 
#define  T_AlterDomainStmt 241 
#define  T_AlterEnumStmt 240 
#define  T_AlterEventTrigStmt 239 
#define  T_AlterExtensionContentsStmt 238 
#define  T_AlterExtensionStmt 237 
#define  T_AlterFdwStmt 236 
#define  T_AlterForeignServerStmt 235 
#define  T_AlterFunctionStmt 234 
#define  T_AlterObjectDependsStmt 233 
#define  T_AlterObjectSchemaStmt 232 
#define  T_AlterOpFamilyStmt 231 
#define  T_AlterOperatorStmt 230 
#define  T_AlterOwnerStmt 229 
#define  T_AlterPolicyStmt 228 
#define  T_AlterPublicationStmt 227 
#define  T_AlterRoleSetStmt 226 
#define  T_AlterRoleStmt 225 
#define  T_AlterSeqStmt 224 
#define  T_AlterStatsStmt 223 
#define  T_AlterSubscriptionStmt 222 
#define  T_AlterSystemStmt 221 
#define  T_AlterTSConfigurationStmt 220 
#define  T_AlterTSDictionaryStmt 219 
#define  T_AlterTableMoveAllStmt 218 
#define  T_AlterTableSpaceOptionsStmt 217 
#define  T_AlterTableStmt 216 
#define  T_AlterUserMappingStmt 215 
#define  T_CallStmt 214 
#define  T_CheckPointStmt 213 
#define  T_ClosePortalStmt 212 
#define  T_ClusterStmt 211 
#define  T_CommentStmt 210 
#define  T_CompositeTypeStmt 209 
#define  T_ConstraintsSetStmt 208 
#define  T_CopyStmt 207 
#define  T_CreateAmStmt 206 
#define  T_CreateCastStmt 205 
#define  T_CreateConversionStmt 204 
#define  T_CreateDomainStmt 203 
#define  T_CreateEnumStmt 202 
#define  T_CreateEventTrigStmt 201 
#define  T_CreateExtensionStmt 200 
#define  T_CreateFdwStmt 199 
#define  T_CreateForeignServerStmt 198 
#define  T_CreateForeignTableStmt 197 
#define  T_CreateFunctionStmt 196 
#define  T_CreateOpClassStmt 195 
#define  T_CreateOpFamilyStmt 194 
#define  T_CreatePLangStmt 193 
#define  T_CreatePolicyStmt 192 
#define  T_CreatePublicationStmt 191 
#define  T_CreateRangeStmt 190 
#define  T_CreateRoleStmt 189 
#define  T_CreateSchemaStmt 188 
#define  T_CreateSeqStmt 187 
#define  T_CreateStatsStmt 186 
#define  T_CreateStmt 185 
#define  T_CreateSubscriptionStmt 184 
#define  T_CreateTableAsStmt 183 
#define  T_CreateTableSpaceStmt 182 
#define  T_CreateTransformStmt 181 
#define  T_CreateTrigStmt 180 
#define  T_CreateUserMappingStmt 179 
#define  T_CreatedbStmt 178 
#define  T_DeallocateStmt 177 
#define  T_DeclareCursorStmt 176 
#define  T_DefineStmt 175 
#define  T_DeleteStmt 174 
#define  T_DiscardStmt 173 
#define  T_DoStmt 172 
#define  T_DropOwnedStmt 171 
#define  T_DropRoleStmt 170 
#define  T_DropStmt 169 
#define  T_DropSubscriptionStmt 168 
#define  T_DropTableSpaceStmt 167 
#define  T_DropUserMappingStmt 166 
#define  T_DropdbStmt 165 
#define  T_ExecuteStmt 164 
#define  T_ExplainStmt 163 
#define  T_FetchStmt 162 
#define  T_GrantRoleStmt 161 
#define  T_GrantStmt 160 
#define  T_ImportForeignSchemaStmt 159 
#define  T_IndexStmt 158 
#define  T_InsertStmt 157 
#define  T_ListenStmt 156 
#define  T_LoadStmt 155 
#define  T_LockStmt 154 
#define  T_NotifyStmt 153 
#define  T_PlannedStmt 152 
#define  T_PrepareStmt 151 
#define  T_Query 150 
#define  T_RawStmt 149 
#define  T_ReassignOwnedStmt 148 
#define  T_RefreshMatViewStmt 147 
#define  T_ReindexStmt 146 
#define  T_RenameStmt 145 
#define  T_RuleStmt 144 
#define  T_SecLabelStmt 143 
#define  T_SelectStmt 142 
#define  T_TransactionStmt 141 
#define  T_TruncateStmt 140 
#define  T_UnlistenStmt 139 
#define  T_UpdateStmt 138 
#define  T_VacuumStmt 137 
#define  T_VariableSetStmt 136 
#define  T_VariableShowStmt 135 
#define  T_ViewStmt 134 
#define  VAR_RESET 133 
#define  VAR_RESET_ALL 132 
#define  VAR_SET_CURRENT 131 
#define  VAR_SET_DEFAULT 130 
#define  VAR_SET_MULTI 129 
#define  VAR_SET_VALUE 128 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ linitial (int /*<<< orphan*/ ) ; 
 int nodeTag (int /*<<< orphan*/ *) ; 

const char *
CreateCommandTag(Node *parsetree)
{
	const char *tag;

	switch (nodeTag(parsetree))
	{
			/* recurse if we're given a RawStmt */
		case T_RawStmt:
			tag = CreateCommandTag(((RawStmt *) parsetree)->stmt);
			break;

			/* raw plannable queries */
		case T_InsertStmt:
			tag = "INSERT";
			break;

		case T_DeleteStmt:
			tag = "DELETE";
			break;

		case T_UpdateStmt:
			tag = "UPDATE";
			break;

		case T_SelectStmt:
			tag = "SELECT";
			break;

			/* utility statements --- same whether raw or cooked */
		case T_TransactionStmt:
			{
				TransactionStmt *stmt = (TransactionStmt *) parsetree;

				switch (stmt->kind)
				{
					case TRANS_STMT_BEGIN:
						tag = "BEGIN";
						break;

					case TRANS_STMT_START:
						tag = "START TRANSACTION";
						break;

					case TRANS_STMT_COMMIT:
						tag = "COMMIT";
						break;

					case TRANS_STMT_ROLLBACK:
					case TRANS_STMT_ROLLBACK_TO:
						tag = "ROLLBACK";
						break;

					case TRANS_STMT_SAVEPOINT:
						tag = "SAVEPOINT";
						break;

					case TRANS_STMT_RELEASE:
						tag = "RELEASE";
						break;

					case TRANS_STMT_PREPARE:
						tag = "PREPARE TRANSACTION";
						break;

					case TRANS_STMT_COMMIT_PREPARED:
						tag = "COMMIT PREPARED";
						break;

					case TRANS_STMT_ROLLBACK_PREPARED:
						tag = "ROLLBACK PREPARED";
						break;

					default:
						tag = "???";
						break;
				}
			}
			break;

		case T_DeclareCursorStmt:
			tag = "DECLARE CURSOR";
			break;

		case T_ClosePortalStmt:
			{
				ClosePortalStmt *stmt = (ClosePortalStmt *) parsetree;

				if (stmt->portalname == NULL)
					tag = "CLOSE CURSOR ALL";
				else
					tag = "CLOSE CURSOR";
			}
			break;

		case T_FetchStmt:
			{
				FetchStmt  *stmt = (FetchStmt *) parsetree;

				tag = (stmt->ismove) ? "MOVE" : "FETCH";
			}
			break;

		case T_CreateDomainStmt:
			tag = "CREATE DOMAIN";
			break;

		case T_CreateSchemaStmt:
			tag = "CREATE SCHEMA";
			break;

		case T_CreateStmt:
			tag = "CREATE TABLE";
			break;

		case T_CreateTableSpaceStmt:
			tag = "CREATE TABLESPACE";
			break;

		case T_DropTableSpaceStmt:
			tag = "DROP TABLESPACE";
			break;

		case T_AlterTableSpaceOptionsStmt:
			tag = "ALTER TABLESPACE";
			break;

		case T_CreateExtensionStmt:
			tag = "CREATE EXTENSION";
			break;

		case T_AlterExtensionStmt:
			tag = "ALTER EXTENSION";
			break;

		case T_AlterExtensionContentsStmt:
			tag = "ALTER EXTENSION";
			break;

		case T_CreateFdwStmt:
			tag = "CREATE FOREIGN DATA WRAPPER";
			break;

		case T_AlterFdwStmt:
			tag = "ALTER FOREIGN DATA WRAPPER";
			break;

		case T_CreateForeignServerStmt:
			tag = "CREATE SERVER";
			break;

		case T_AlterForeignServerStmt:
			tag = "ALTER SERVER";
			break;

		case T_CreateUserMappingStmt:
			tag = "CREATE USER MAPPING";
			break;

		case T_AlterUserMappingStmt:
			tag = "ALTER USER MAPPING";
			break;

		case T_DropUserMappingStmt:
			tag = "DROP USER MAPPING";
			break;

		case T_CreateForeignTableStmt:
			tag = "CREATE FOREIGN TABLE";
			break;

		case T_ImportForeignSchemaStmt:
			tag = "IMPORT FOREIGN SCHEMA";
			break;

		case T_DropStmt:
			switch (((DropStmt *) parsetree)->removeType)
			{
				case OBJECT_TABLE:
					tag = "DROP TABLE";
					break;
				case OBJECT_SEQUENCE:
					tag = "DROP SEQUENCE";
					break;
				case OBJECT_VIEW:
					tag = "DROP VIEW";
					break;
				case OBJECT_MATVIEW:
					tag = "DROP MATERIALIZED VIEW";
					break;
				case OBJECT_INDEX:
					tag = "DROP INDEX";
					break;
				case OBJECT_TYPE:
					tag = "DROP TYPE";
					break;
				case OBJECT_DOMAIN:
					tag = "DROP DOMAIN";
					break;
				case OBJECT_COLLATION:
					tag = "DROP COLLATION";
					break;
				case OBJECT_CONVERSION:
					tag = "DROP CONVERSION";
					break;
				case OBJECT_SCHEMA:
					tag = "DROP SCHEMA";
					break;
				case OBJECT_TSPARSER:
					tag = "DROP TEXT SEARCH PARSER";
					break;
				case OBJECT_TSDICTIONARY:
					tag = "DROP TEXT SEARCH DICTIONARY";
					break;
				case OBJECT_TSTEMPLATE:
					tag = "DROP TEXT SEARCH TEMPLATE";
					break;
				case OBJECT_TSCONFIGURATION:
					tag = "DROP TEXT SEARCH CONFIGURATION";
					break;
				case OBJECT_FOREIGN_TABLE:
					tag = "DROP FOREIGN TABLE";
					break;
				case OBJECT_EXTENSION:
					tag = "DROP EXTENSION";
					break;
				case OBJECT_FUNCTION:
					tag = "DROP FUNCTION";
					break;
				case OBJECT_PROCEDURE:
					tag = "DROP PROCEDURE";
					break;
				case OBJECT_ROUTINE:
					tag = "DROP ROUTINE";
					break;
				case OBJECT_AGGREGATE:
					tag = "DROP AGGREGATE";
					break;
				case OBJECT_OPERATOR:
					tag = "DROP OPERATOR";
					break;
				case OBJECT_LANGUAGE:
					tag = "DROP LANGUAGE";
					break;
				case OBJECT_CAST:
					tag = "DROP CAST";
					break;
				case OBJECT_TRIGGER:
					tag = "DROP TRIGGER";
					break;
				case OBJECT_EVENT_TRIGGER:
					tag = "DROP EVENT TRIGGER";
					break;
				case OBJECT_RULE:
					tag = "DROP RULE";
					break;
				case OBJECT_FDW:
					tag = "DROP FOREIGN DATA WRAPPER";
					break;
				case OBJECT_FOREIGN_SERVER:
					tag = "DROP SERVER";
					break;
				case OBJECT_OPCLASS:
					tag = "DROP OPERATOR CLASS";
					break;
				case OBJECT_OPFAMILY:
					tag = "DROP OPERATOR FAMILY";
					break;
				case OBJECT_POLICY:
					tag = "DROP POLICY";
					break;
				case OBJECT_TRANSFORM:
					tag = "DROP TRANSFORM";
					break;
				case OBJECT_ACCESS_METHOD:
					tag = "DROP ACCESS METHOD";
					break;
				case OBJECT_PUBLICATION:
					tag = "DROP PUBLICATION";
					break;
				case OBJECT_STATISTIC_EXT:
					tag = "DROP STATISTICS";
					break;
				default:
					tag = "???";
			}
			break;

		case T_TruncateStmt:
			tag = "TRUNCATE TABLE";
			break;

		case T_CommentStmt:
			tag = "COMMENT";
			break;

		case T_SecLabelStmt:
			tag = "SECURITY LABEL";
			break;

		case T_CopyStmt:
			tag = "COPY";
			break;

		case T_RenameStmt:
			/*
			 * When the column is renamed, the command tag is created
			 * from its relation type
			 */
			tag = AlterObjectTypeCommandTag(
				((RenameStmt *) parsetree)->renameType == OBJECT_COLUMN ?
				((RenameStmt *) parsetree)->relationType :
				((RenameStmt *) parsetree)->renameType);
			break;

		case T_AlterObjectDependsStmt:
			tag = AlterObjectTypeCommandTag(((AlterObjectDependsStmt *) parsetree)->objectType);
			break;

		case T_AlterObjectSchemaStmt:
			tag = AlterObjectTypeCommandTag(((AlterObjectSchemaStmt *) parsetree)->objectType);
			break;

		case T_AlterOwnerStmt:
			tag = AlterObjectTypeCommandTag(((AlterOwnerStmt *) parsetree)->objectType);
			break;

		case T_AlterTableMoveAllStmt:
			tag = AlterObjectTypeCommandTag(((AlterTableMoveAllStmt *) parsetree)->objtype);
			break;

		case T_AlterTableStmt:
			tag = AlterObjectTypeCommandTag(((AlterTableStmt *) parsetree)->relkind);
			break;

		case T_AlterDomainStmt:
			tag = "ALTER DOMAIN";
			break;

		case T_AlterFunctionStmt:
			switch (((AlterFunctionStmt *) parsetree)->objtype)
			{
				case OBJECT_FUNCTION:
					tag = "ALTER FUNCTION";
					break;
				case OBJECT_PROCEDURE:
					tag = "ALTER PROCEDURE";
					break;
				case OBJECT_ROUTINE:
					tag = "ALTER ROUTINE";
					break;
				default:
					tag = "???";
			}
			break;

		case T_GrantStmt:
			{
				GrantStmt  *stmt = (GrantStmt *) parsetree;

				tag = (stmt->is_grant) ? "GRANT" : "REVOKE";
			}
			break;

		case T_GrantRoleStmt:
			{
				GrantRoleStmt *stmt = (GrantRoleStmt *) parsetree;

				tag = (stmt->is_grant) ? "GRANT ROLE" : "REVOKE ROLE";
			}
			break;

		case T_AlterDefaultPrivilegesStmt:
			tag = "ALTER DEFAULT PRIVILEGES";
			break;

		case T_DefineStmt:
			switch (((DefineStmt *) parsetree)->kind)
			{
				case OBJECT_AGGREGATE:
					tag = "CREATE AGGREGATE";
					break;
				case OBJECT_OPERATOR:
					tag = "CREATE OPERATOR";
					break;
				case OBJECT_TYPE:
					tag = "CREATE TYPE";
					break;
				case OBJECT_TSPARSER:
					tag = "CREATE TEXT SEARCH PARSER";
					break;
				case OBJECT_TSDICTIONARY:
					tag = "CREATE TEXT SEARCH DICTIONARY";
					break;
				case OBJECT_TSTEMPLATE:
					tag = "CREATE TEXT SEARCH TEMPLATE";
					break;
				case OBJECT_TSCONFIGURATION:
					tag = "CREATE TEXT SEARCH CONFIGURATION";
					break;
				case OBJECT_COLLATION:
					tag = "CREATE COLLATION";
					break;
				case OBJECT_ACCESS_METHOD:
					tag = "CREATE ACCESS METHOD";
					break;
				default:
					tag = "???";
			}
			break;

		case T_CompositeTypeStmt:
			tag = "CREATE TYPE";
			break;

		case T_CreateEnumStmt:
			tag = "CREATE TYPE";
			break;

		case T_CreateRangeStmt:
			tag = "CREATE TYPE";
			break;

		case T_AlterEnumStmt:
			tag = "ALTER TYPE";
			break;

		case T_ViewStmt:
			tag = "CREATE VIEW";
			break;

		case T_CreateFunctionStmt:
			if (((CreateFunctionStmt *) parsetree)->is_procedure)
				tag = "CREATE PROCEDURE";
			else
				tag = "CREATE FUNCTION";
			break;

		case T_IndexStmt:
			tag = "CREATE INDEX";
			break;

		case T_RuleStmt:
			tag = "CREATE RULE";
			break;

		case T_CreateSeqStmt:
			tag = "CREATE SEQUENCE";
			break;

		case T_AlterSeqStmt:
			tag = "ALTER SEQUENCE";
			break;

		case T_DoStmt:
			tag = "DO";
			break;

		case T_CreatedbStmt:
			tag = "CREATE DATABASE";
			break;

		case T_AlterDatabaseStmt:
			tag = "ALTER DATABASE";
			break;

		case T_AlterDatabaseSetStmt:
			tag = "ALTER DATABASE";
			break;

		case T_DropdbStmt:
			tag = "DROP DATABASE";
			break;

		case T_NotifyStmt:
			tag = "NOTIFY";
			break;

		case T_ListenStmt:
			tag = "LISTEN";
			break;

		case T_UnlistenStmt:
			tag = "UNLISTEN";
			break;

		case T_LoadStmt:
			tag = "LOAD";
			break;

		case T_CallStmt:
			tag = "CALL";
			break;

		case T_ClusterStmt:
			tag = "CLUSTER";
			break;

		case T_VacuumStmt:
			if (((VacuumStmt *) parsetree)->is_vacuumcmd)
				tag = "VACUUM";
			else
				tag = "ANALYZE";
			break;

		case T_ExplainStmt:
			tag = "EXPLAIN";
			break;

		case T_CreateTableAsStmt:
			switch (((CreateTableAsStmt *) parsetree)->relkind)
			{
				case OBJECT_TABLE:
					if (((CreateTableAsStmt *) parsetree)->is_select_into)
						tag = "SELECT INTO";
					else
						tag = "CREATE TABLE AS";
					break;
				case OBJECT_MATVIEW:
					tag = "CREATE MATERIALIZED VIEW";
					break;
				default:
					tag = "???";
			}
			break;

		case T_RefreshMatViewStmt:
			tag = "REFRESH MATERIALIZED VIEW";
			break;

		case T_AlterSystemStmt:
			tag = "ALTER SYSTEM";
			break;

		case T_VariableSetStmt:
			switch (((VariableSetStmt *) parsetree)->kind)
			{
				case VAR_SET_VALUE:
				case VAR_SET_CURRENT:
				case VAR_SET_DEFAULT:
				case VAR_SET_MULTI:
					tag = "SET";
					break;
				case VAR_RESET:
				case VAR_RESET_ALL:
					tag = "RESET";
					break;
				default:
					tag = "???";
			}
			break;

		case T_VariableShowStmt:
			tag = "SHOW";
			break;

		case T_DiscardStmt:
			switch (((DiscardStmt *) parsetree)->target)
			{
				case DISCARD_ALL:
					tag = "DISCARD ALL";
					break;
				case DISCARD_PLANS:
					tag = "DISCARD PLANS";
					break;
				case DISCARD_TEMP:
					tag = "DISCARD TEMP";
					break;
				case DISCARD_SEQUENCES:
					tag = "DISCARD SEQUENCES";
					break;
				default:
					tag = "???";
			}
			break;

		case T_CreateTransformStmt:
			tag = "CREATE TRANSFORM";
			break;

		case T_CreateTrigStmt:
			tag = "CREATE TRIGGER";
			break;

		case T_CreateEventTrigStmt:
			tag = "CREATE EVENT TRIGGER";
			break;

		case T_AlterEventTrigStmt:
			tag = "ALTER EVENT TRIGGER";
			break;

		case T_CreatePLangStmt:
			tag = "CREATE LANGUAGE";
			break;

		case T_CreateRoleStmt:
			tag = "CREATE ROLE";
			break;

		case T_AlterRoleStmt:
			tag = "ALTER ROLE";
			break;

		case T_AlterRoleSetStmt:
			tag = "ALTER ROLE";
			break;

		case T_DropRoleStmt:
			tag = "DROP ROLE";
			break;

		case T_DropOwnedStmt:
			tag = "DROP OWNED";
			break;

		case T_ReassignOwnedStmt:
			tag = "REASSIGN OWNED";
			break;

		case T_LockStmt:
			tag = "LOCK TABLE";
			break;

		case T_ConstraintsSetStmt:
			tag = "SET CONSTRAINTS";
			break;

		case T_CheckPointStmt:
			tag = "CHECKPOINT";
			break;

		case T_ReindexStmt:
			tag = "REINDEX";
			break;

		case T_CreateConversionStmt:
			tag = "CREATE CONVERSION";
			break;

		case T_CreateCastStmt:
			tag = "CREATE CAST";
			break;

		case T_CreateOpClassStmt:
			tag = "CREATE OPERATOR CLASS";
			break;

		case T_CreateOpFamilyStmt:
			tag = "CREATE OPERATOR FAMILY";
			break;

		case T_AlterOpFamilyStmt:
			tag = "ALTER OPERATOR FAMILY";
			break;

		case T_AlterOperatorStmt:
			tag = "ALTER OPERATOR";
			break;

		case T_AlterTSDictionaryStmt:
			tag = "ALTER TEXT SEARCH DICTIONARY";
			break;

		case T_AlterTSConfigurationStmt:
			tag = "ALTER TEXT SEARCH CONFIGURATION";
			break;

		case T_CreatePolicyStmt:
			tag = "CREATE POLICY";
			break;

		case T_AlterPolicyStmt:
			tag = "ALTER POLICY";
			break;

		case T_CreateAmStmt:
			tag = "CREATE ACCESS METHOD";
			break;

		case T_CreatePublicationStmt:
			tag = "CREATE PUBLICATION";
			break;

		case T_AlterPublicationStmt:
			tag = "ALTER PUBLICATION";
			break;

		case T_CreateSubscriptionStmt:
			tag = "CREATE SUBSCRIPTION";
			break;

		case T_AlterSubscriptionStmt:
			tag = "ALTER SUBSCRIPTION";
			break;

		case T_DropSubscriptionStmt:
			tag = "DROP SUBSCRIPTION";
			break;

		case T_AlterCollationStmt:
			tag = "ALTER COLLATION";
			break;

		case T_PrepareStmt:
			tag = "PREPARE";
			break;

		case T_ExecuteStmt:
			tag = "EXECUTE";
			break;

		case T_CreateStatsStmt:
			tag = "CREATE STATISTICS";
			break;

		case T_AlterStatsStmt:
			tag = "ALTER STATISTICS";
			break;

		case T_DeallocateStmt:
			{
				DeallocateStmt *stmt = (DeallocateStmt *) parsetree;

				if (stmt->name == NULL)
					tag = "DEALLOCATE ALL";
				else
					tag = "DEALLOCATE";
			}
			break;

			/* already-planned queries */
		case T_PlannedStmt:
			{
				PlannedStmt *stmt = (PlannedStmt *) parsetree;

				switch (stmt->commandType)
				{
					case CMD_SELECT:

						/*
						 * We take a little extra care here so that the result
						 * will be useful for complaints about read-only
						 * statements
						 */
						if (stmt->rowMarks != NIL)
						{
							/* not 100% but probably close enough */
							switch (((PlanRowMark *) linitial(stmt->rowMarks))->strength)
							{
								case LCS_FORKEYSHARE:
									tag = "SELECT FOR KEY SHARE";
									break;
								case LCS_FORSHARE:
									tag = "SELECT FOR SHARE";
									break;
								case LCS_FORNOKEYUPDATE:
									tag = "SELECT FOR NO KEY UPDATE";
									break;
								case LCS_FORUPDATE:
									tag = "SELECT FOR UPDATE";
									break;
								default:
									tag = "SELECT";
									break;
							}
						}
						else
							tag = "SELECT";
						break;
					case CMD_UPDATE:
						tag = "UPDATE";
						break;
					case CMD_INSERT:
						tag = "INSERT";
						break;
					case CMD_DELETE:
						tag = "DELETE";
						break;
					case CMD_UTILITY:
						tag = CreateCommandTag(stmt->utilityStmt);
						break;
					default:
						elog(WARNING, "unrecognized commandType: %d",
							 (int) stmt->commandType);
						tag = "???";
						break;
				}
			}
			break;

			/* parsed-and-rewritten-but-not-planned queries */
		case T_Query:
			{
				Query	   *stmt = (Query *) parsetree;

				switch (stmt->commandType)
				{
					case CMD_SELECT:

						/*
						 * We take a little extra care here so that the result
						 * will be useful for complaints about read-only
						 * statements
						 */
						if (stmt->rowMarks != NIL)
						{
							/* not 100% but probably close enough */
							switch (((RowMarkClause *) linitial(stmt->rowMarks))->strength)
							{
								case LCS_FORKEYSHARE:
									tag = "SELECT FOR KEY SHARE";
									break;
								case LCS_FORSHARE:
									tag = "SELECT FOR SHARE";
									break;
								case LCS_FORNOKEYUPDATE:
									tag = "SELECT FOR NO KEY UPDATE";
									break;
								case LCS_FORUPDATE:
									tag = "SELECT FOR UPDATE";
									break;
								default:
									tag = "???";
									break;
							}
						}
						else
							tag = "SELECT";
						break;
					case CMD_UPDATE:
						tag = "UPDATE";
						break;
					case CMD_INSERT:
						tag = "INSERT";
						break;
					case CMD_DELETE:
						tag = "DELETE";
						break;
					case CMD_UTILITY:
						tag = CreateCommandTag(stmt->utilityStmt);
						break;
					default:
						elog(WARNING, "unrecognized commandType: %d",
							 (int) stmt->commandType);
						tag = "???";
						break;
				}
			}
			break;

		default:
			elog(WARNING, "unrecognized node type: %d",
				 (int) nodeTag(parsetree));
			tag = "???";
			break;
	}

	return tag;
}