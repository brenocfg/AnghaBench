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
typedef  int ObjectType ;
typedef  int AclResult ;

/* Variables and functions */
#define  ACLCHECK_NOT_OWNER 180 
#define  ACLCHECK_NO_PRIV 179 
#define  ACLCHECK_OK 178 
 int /*<<< orphan*/  ERRCODE_INSUFFICIENT_PRIVILEGE ; 
 int /*<<< orphan*/  ERROR ; 
#define  OBJECT_ACCESS_METHOD 177 
#define  OBJECT_AGGREGATE 176 
#define  OBJECT_AMOP 175 
#define  OBJECT_AMPROC 174 
#define  OBJECT_ATTRIBUTE 173 
#define  OBJECT_CAST 172 
#define  OBJECT_COLLATION 171 
#define  OBJECT_COLUMN 170 
#define  OBJECT_CONVERSION 169 
#define  OBJECT_DATABASE 168 
#define  OBJECT_DEFACL 167 
#define  OBJECT_DEFAULT 166 
#define  OBJECT_DOMAIN 165 
#define  OBJECT_DOMCONSTRAINT 164 
#define  OBJECT_EVENT_TRIGGER 163 
#define  OBJECT_EXTENSION 162 
#define  OBJECT_FDW 161 
#define  OBJECT_FOREIGN_SERVER 160 
#define  OBJECT_FOREIGN_TABLE 159 
#define  OBJECT_FUNCTION 158 
#define  OBJECT_INDEX 157 
#define  OBJECT_LANGUAGE 156 
#define  OBJECT_LARGEOBJECT 155 
#define  OBJECT_MATVIEW 154 
#define  OBJECT_OPCLASS 153 
#define  OBJECT_OPERATOR 152 
#define  OBJECT_OPFAMILY 151 
#define  OBJECT_POLICY 150 
#define  OBJECT_PROCEDURE 149 
#define  OBJECT_PUBLICATION 148 
#define  OBJECT_PUBLICATION_REL 147 
#define  OBJECT_ROLE 146 
#define  OBJECT_ROUTINE 145 
#define  OBJECT_RULE 144 
#define  OBJECT_SCHEMA 143 
#define  OBJECT_SEQUENCE 142 
#define  OBJECT_STATISTIC_EXT 141 
#define  OBJECT_SUBSCRIPTION 140 
#define  OBJECT_TABCONSTRAINT 139 
#define  OBJECT_TABLE 138 
#define  OBJECT_TABLESPACE 137 
#define  OBJECT_TRANSFORM 136 
#define  OBJECT_TRIGGER 135 
#define  OBJECT_TSCONFIGURATION 134 
#define  OBJECT_TSDICTIONARY 133 
#define  OBJECT_TSPARSER 132 
#define  OBJECT_TSTEMPLATE 131 
#define  OBJECT_TYPE 130 
#define  OBJECT_USER_MAPPING 129 
#define  OBJECT_VIEW 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char const*,char const*) ; 
 char* gettext_noop (char*) ; 

void
aclcheck_error(AclResult aclerr, ObjectType objtype,
			   const char *objectname)
{
	switch (aclerr)
	{
		case ACLCHECK_OK:
			/* no error, so return to caller */
			break;
		case ACLCHECK_NO_PRIV:
			{
				const char *msg = "???";

				switch (objtype)
				{
					case OBJECT_AGGREGATE:
						msg = gettext_noop("permission denied for aggregate %s");
						break;
					case OBJECT_COLLATION:
						msg = gettext_noop("permission denied for collation %s");
						break;
					case OBJECT_COLUMN:
						msg = gettext_noop("permission denied for column %s");
						break;
					case OBJECT_CONVERSION:
						msg = gettext_noop("permission denied for conversion %s");
						break;
					case OBJECT_DATABASE:
						msg = gettext_noop("permission denied for database %s");
						break;
					case OBJECT_DOMAIN:
						msg = gettext_noop("permission denied for domain %s");
						break;
					case OBJECT_EVENT_TRIGGER:
						msg = gettext_noop("permission denied for event trigger %s");
						break;
					case OBJECT_EXTENSION:
						msg = gettext_noop("permission denied for extension %s");
						break;
					case OBJECT_FDW:
						msg = gettext_noop("permission denied for foreign-data wrapper %s");
						break;
					case OBJECT_FOREIGN_SERVER:
						msg = gettext_noop("permission denied for foreign server %s");
						break;
					case OBJECT_FOREIGN_TABLE:
						msg = gettext_noop("permission denied for foreign table %s");
						break;
					case OBJECT_FUNCTION:
						msg = gettext_noop("permission denied for function %s");
						break;
					case OBJECT_INDEX:
						msg = gettext_noop("permission denied for index %s");
						break;
					case OBJECT_LANGUAGE:
						msg = gettext_noop("permission denied for language %s");
						break;
					case OBJECT_LARGEOBJECT:
						msg = gettext_noop("permission denied for large object %s");
						break;
					case OBJECT_MATVIEW:
						msg = gettext_noop("permission denied for materialized view %s");
						break;
					case OBJECT_OPCLASS:
						msg = gettext_noop("permission denied for operator class %s");
						break;
					case OBJECT_OPERATOR:
						msg = gettext_noop("permission denied for operator %s");
						break;
					case OBJECT_OPFAMILY:
						msg = gettext_noop("permission denied for operator family %s");
						break;
					case OBJECT_POLICY:
						msg = gettext_noop("permission denied for policy %s");
						break;
					case OBJECT_PROCEDURE:
						msg = gettext_noop("permission denied for procedure %s");
						break;
					case OBJECT_PUBLICATION:
						msg = gettext_noop("permission denied for publication %s");
						break;
					case OBJECT_ROUTINE:
						msg = gettext_noop("permission denied for routine %s");
						break;
					case OBJECT_SCHEMA:
						msg = gettext_noop("permission denied for schema %s");
						break;
					case OBJECT_SEQUENCE:
						msg = gettext_noop("permission denied for sequence %s");
						break;
					case OBJECT_STATISTIC_EXT:
						msg = gettext_noop("permission denied for statistics object %s");
						break;
					case OBJECT_SUBSCRIPTION:
						msg = gettext_noop("permission denied for subscription %s");
						break;
					case OBJECT_TABLE:
						msg = gettext_noop("permission denied for table %s");
						break;
					case OBJECT_TABLESPACE:
						msg = gettext_noop("permission denied for tablespace %s");
						break;
					case OBJECT_TSCONFIGURATION:
						msg = gettext_noop("permission denied for text search configuration %s");
						break;
					case OBJECT_TSDICTIONARY:
						msg = gettext_noop("permission denied for text search dictionary %s");
						break;
					case OBJECT_TYPE:
						msg = gettext_noop("permission denied for type %s");
						break;
					case OBJECT_VIEW:
						msg = gettext_noop("permission denied for view %s");
						break;
						/* these currently aren't used */
					case OBJECT_ACCESS_METHOD:
					case OBJECT_AMOP:
					case OBJECT_AMPROC:
					case OBJECT_ATTRIBUTE:
					case OBJECT_CAST:
					case OBJECT_DEFAULT:
					case OBJECT_DEFACL:
					case OBJECT_DOMCONSTRAINT:
					case OBJECT_PUBLICATION_REL:
					case OBJECT_ROLE:
					case OBJECT_RULE:
					case OBJECT_TABCONSTRAINT:
					case OBJECT_TRANSFORM:
					case OBJECT_TRIGGER:
					case OBJECT_TSPARSER:
					case OBJECT_TSTEMPLATE:
					case OBJECT_USER_MAPPING:
						elog(ERROR, "unsupported object type %d", objtype);
				}

				ereport(ERROR,
						(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
						 errmsg(msg, objectname)));
				break;
			}
		case ACLCHECK_NOT_OWNER:
			{
				const char *msg = "???";

				switch (objtype)
				{
					case OBJECT_AGGREGATE:
						msg = gettext_noop("must be owner of aggregate %s");
						break;
					case OBJECT_COLLATION:
						msg = gettext_noop("must be owner of collation %s");
						break;
					case OBJECT_CONVERSION:
						msg = gettext_noop("must be owner of conversion %s");
						break;
					case OBJECT_DATABASE:
						msg = gettext_noop("must be owner of database %s");
						break;
					case OBJECT_DOMAIN:
						msg = gettext_noop("must be owner of domain %s");
						break;
					case OBJECT_EVENT_TRIGGER:
						msg = gettext_noop("must be owner of event trigger %s");
						break;
					case OBJECT_EXTENSION:
						msg = gettext_noop("must be owner of extension %s");
						break;
					case OBJECT_FDW:
						msg = gettext_noop("must be owner of foreign-data wrapper %s");
						break;
					case OBJECT_FOREIGN_SERVER:
						msg = gettext_noop("must be owner of foreign server %s");
						break;
					case OBJECT_FOREIGN_TABLE:
						msg = gettext_noop("must be owner of foreign table %s");
						break;
					case OBJECT_FUNCTION:
						msg = gettext_noop("must be owner of function %s");
						break;
					case OBJECT_INDEX:
						msg = gettext_noop("must be owner of index %s");
						break;
					case OBJECT_LANGUAGE:
						msg = gettext_noop("must be owner of language %s");
						break;
					case OBJECT_LARGEOBJECT:
						msg = gettext_noop("must be owner of large object %s");
						break;
					case OBJECT_MATVIEW:
						msg = gettext_noop("must be owner of materialized view %s");
						break;
					case OBJECT_OPCLASS:
						msg = gettext_noop("must be owner of operator class %s");
						break;
					case OBJECT_OPERATOR:
						msg = gettext_noop("must be owner of operator %s");
						break;
					case OBJECT_OPFAMILY:
						msg = gettext_noop("must be owner of operator family %s");
						break;
					case OBJECT_PROCEDURE:
						msg = gettext_noop("must be owner of procedure %s");
						break;
					case OBJECT_PUBLICATION:
						msg = gettext_noop("must be owner of publication %s");
						break;
					case OBJECT_ROUTINE:
						msg = gettext_noop("must be owner of routine %s");
						break;
					case OBJECT_SEQUENCE:
						msg = gettext_noop("must be owner of sequence %s");
						break;
					case OBJECT_SUBSCRIPTION:
						msg = gettext_noop("must be owner of subscription %s");
						break;
					case OBJECT_TABLE:
						msg = gettext_noop("must be owner of table %s");
						break;
					case OBJECT_TYPE:
						msg = gettext_noop("must be owner of type %s");
						break;
					case OBJECT_VIEW:
						msg = gettext_noop("must be owner of view %s");
						break;
					case OBJECT_SCHEMA:
						msg = gettext_noop("must be owner of schema %s");
						break;
					case OBJECT_STATISTIC_EXT:
						msg = gettext_noop("must be owner of statistics object %s");
						break;
					case OBJECT_TABLESPACE:
						msg = gettext_noop("must be owner of tablespace %s");
						break;
					case OBJECT_TSCONFIGURATION:
						msg = gettext_noop("must be owner of text search configuration %s");
						break;
					case OBJECT_TSDICTIONARY:
						msg = gettext_noop("must be owner of text search dictionary %s");
						break;

						/*
						 * Special cases: For these, the error message talks
						 * about "relation", because that's where the
						 * ownership is attached.  See also
						 * check_object_ownership().
						 */
					case OBJECT_COLUMN:
					case OBJECT_POLICY:
					case OBJECT_RULE:
					case OBJECT_TABCONSTRAINT:
					case OBJECT_TRIGGER:
						msg = gettext_noop("must be owner of relation %s");
						break;
						/* these currently aren't used */
					case OBJECT_ACCESS_METHOD:
					case OBJECT_AMOP:
					case OBJECT_AMPROC:
					case OBJECT_ATTRIBUTE:
					case OBJECT_CAST:
					case OBJECT_DEFAULT:
					case OBJECT_DEFACL:
					case OBJECT_DOMCONSTRAINT:
					case OBJECT_PUBLICATION_REL:
					case OBJECT_ROLE:
					case OBJECT_TRANSFORM:
					case OBJECT_TSPARSER:
					case OBJECT_TSTEMPLATE:
					case OBJECT_USER_MAPPING:
						elog(ERROR, "unsupported object type %d", objtype);
				}

				ereport(ERROR,
						(errcode(ERRCODE_INSUFFICIENT_PRIVILEGE),
						 errmsg(msg, objectname)));
				break;
			}
		default:
			elog(ERROR, "unrecognized AclResult: %d", (int) aclerr);
			break;
	}
}