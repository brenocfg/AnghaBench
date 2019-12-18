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

/* Variables and functions */
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

__attribute__((used)) static const char *
stringify_adefprivs_objtype(ObjectType objtype)
{
	switch (objtype)
	{
		case OBJECT_COLUMN:
			return "COLUMNS";
		case OBJECT_TABLE:
			return "TABLES";
		case OBJECT_SEQUENCE:
			return "SEQUENCES";
		case OBJECT_DATABASE:
			return "DATABASES";
		case OBJECT_DOMAIN:
			return "DOMAINS";
		case OBJECT_FDW:
			return "FOREIGN DATA WRAPPERS";
		case OBJECT_FOREIGN_SERVER:
			return "FOREIGN SERVERS";
		case OBJECT_FUNCTION:
			return "FUNCTIONS";
		case OBJECT_LANGUAGE:
			return "LANGUAGES";
		case OBJECT_LARGEOBJECT:
			return "LARGE OBJECTS";
		case OBJECT_SCHEMA:
			return "SCHEMAS";
		case OBJECT_PROCEDURE:
			return "PROCEDURES";
		case OBJECT_ROUTINE:
			return "ROUTINES";
		case OBJECT_TABLESPACE:
			return "TABLESPACES";
		case OBJECT_TYPE:
			return "TYPES";
			/* these currently aren't used */
		case OBJECT_ACCESS_METHOD:
		case OBJECT_AGGREGATE:
		case OBJECT_AMOP:
		case OBJECT_AMPROC:
		case OBJECT_ATTRIBUTE:
		case OBJECT_CAST:
		case OBJECT_COLLATION:
		case OBJECT_CONVERSION:
		case OBJECT_DEFAULT:
		case OBJECT_DEFACL:
		case OBJECT_DOMCONSTRAINT:
		case OBJECT_EVENT_TRIGGER:
		case OBJECT_EXTENSION:
		case OBJECT_FOREIGN_TABLE:
		case OBJECT_INDEX:
		case OBJECT_MATVIEW:
		case OBJECT_OPCLASS:
		case OBJECT_OPERATOR:
		case OBJECT_OPFAMILY:
		case OBJECT_POLICY:
		case OBJECT_PUBLICATION:
		case OBJECT_PUBLICATION_REL:
		case OBJECT_ROLE:
		case OBJECT_RULE:
		case OBJECT_STATISTIC_EXT:
		case OBJECT_SUBSCRIPTION:
		case OBJECT_TABCONSTRAINT:
		case OBJECT_TRANSFORM:
		case OBJECT_TRIGGER:
		case OBJECT_TSCONFIGURATION:
		case OBJECT_TSDICTIONARY:
		case OBJECT_TSPARSER:
		case OBJECT_TSTEMPLATE:
		case OBJECT_USER_MAPPING:
		case OBJECT_VIEW:
			elog(ERROR, "unsupported object type: %d", (int) objtype);
	}

	return "???";				/* keep compiler quiet */
}