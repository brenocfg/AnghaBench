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
#define  OBJECT_AGGREGATE 169 
#define  OBJECT_ATTRIBUTE 168 
#define  OBJECT_CAST 167 
#define  OBJECT_COLLATION 166 
#define  OBJECT_COLUMN 165 
#define  OBJECT_CONVERSION 164 
#define  OBJECT_DATABASE 163 
#define  OBJECT_DOMAIN 162 
#define  OBJECT_DOMCONSTRAINT 161 
#define  OBJECT_EVENT_TRIGGER 160 
#define  OBJECT_EXTENSION 159 
#define  OBJECT_FDW 158 
#define  OBJECT_FOREIGN_SERVER 157 
#define  OBJECT_FOREIGN_TABLE 156 
#define  OBJECT_FUNCTION 155 
#define  OBJECT_INDEX 154 
#define  OBJECT_LANGUAGE 153 
#define  OBJECT_LARGEOBJECT 152 
#define  OBJECT_MATVIEW 151 
#define  OBJECT_OPCLASS 150 
#define  OBJECT_OPERATOR 149 
#define  OBJECT_OPFAMILY 148 
#define  OBJECT_POLICY 147 
#define  OBJECT_PROCEDURE 146 
#define  OBJECT_PUBLICATION 145 
#define  OBJECT_ROLE 144 
#define  OBJECT_ROUTINE 143 
#define  OBJECT_RULE 142 
#define  OBJECT_SCHEMA 141 
#define  OBJECT_SEQUENCE 140 
#define  OBJECT_STATISTIC_EXT 139 
#define  OBJECT_SUBSCRIPTION 138 
#define  OBJECT_TABCONSTRAINT 137 
#define  OBJECT_TABLE 136 
#define  OBJECT_TABLESPACE 135 
#define  OBJECT_TRIGGER 134 
#define  OBJECT_TSCONFIGURATION 133 
#define  OBJECT_TSDICTIONARY 132 
#define  OBJECT_TSPARSER 131 
#define  OBJECT_TSTEMPLATE 130 
#define  OBJECT_TYPE 129 
#define  OBJECT_VIEW 128 

__attribute__((used)) static const char *
AlterObjectTypeCommandTag(ObjectType objtype)
{
	const char *tag;

	switch (objtype)
	{
		case OBJECT_AGGREGATE:
			tag = "ALTER AGGREGATE";
			break;
		case OBJECT_ATTRIBUTE:
			tag = "ALTER TYPE";
			break;
		case OBJECT_CAST:
			tag = "ALTER CAST";
			break;
		case OBJECT_COLLATION:
			tag = "ALTER COLLATION";
			break;
		case OBJECT_COLUMN:
			tag = "ALTER TABLE";
			break;
		case OBJECT_CONVERSION:
			tag = "ALTER CONVERSION";
			break;
		case OBJECT_DATABASE:
			tag = "ALTER DATABASE";
			break;
		case OBJECT_DOMAIN:
		case OBJECT_DOMCONSTRAINT:
			tag = "ALTER DOMAIN";
			break;
		case OBJECT_EXTENSION:
			tag = "ALTER EXTENSION";
			break;
		case OBJECT_FDW:
			tag = "ALTER FOREIGN DATA WRAPPER";
			break;
		case OBJECT_FOREIGN_SERVER:
			tag = "ALTER SERVER";
			break;
		case OBJECT_FOREIGN_TABLE:
			tag = "ALTER FOREIGN TABLE";
			break;
		case OBJECT_FUNCTION:
			tag = "ALTER FUNCTION";
			break;
		case OBJECT_INDEX:
			tag = "ALTER INDEX";
			break;
		case OBJECT_LANGUAGE:
			tag = "ALTER LANGUAGE";
			break;
		case OBJECT_LARGEOBJECT:
			tag = "ALTER LARGE OBJECT";
			break;
		case OBJECT_OPCLASS:
			tag = "ALTER OPERATOR CLASS";
			break;
		case OBJECT_OPERATOR:
			tag = "ALTER OPERATOR";
			break;
		case OBJECT_OPFAMILY:
			tag = "ALTER OPERATOR FAMILY";
			break;
		case OBJECT_POLICY:
			tag = "ALTER POLICY";
			break;
		case OBJECT_PROCEDURE:
			tag = "ALTER PROCEDURE";
			break;
		case OBJECT_ROLE:
			tag = "ALTER ROLE";
			break;
		case OBJECT_ROUTINE:
			tag = "ALTER ROUTINE";
			break;
		case OBJECT_RULE:
			tag = "ALTER RULE";
			break;
		case OBJECT_SCHEMA:
			tag = "ALTER SCHEMA";
			break;
		case OBJECT_SEQUENCE:
			tag = "ALTER SEQUENCE";
			break;
		case OBJECT_TABLE:
		case OBJECT_TABCONSTRAINT:
			tag = "ALTER TABLE";
			break;
		case OBJECT_TABLESPACE:
			tag = "ALTER TABLESPACE";
			break;
		case OBJECT_TRIGGER:
			tag = "ALTER TRIGGER";
			break;
		case OBJECT_EVENT_TRIGGER:
			tag = "ALTER EVENT TRIGGER";
			break;
		case OBJECT_TSCONFIGURATION:
			tag = "ALTER TEXT SEARCH CONFIGURATION";
			break;
		case OBJECT_TSDICTIONARY:
			tag = "ALTER TEXT SEARCH DICTIONARY";
			break;
		case OBJECT_TSPARSER:
			tag = "ALTER TEXT SEARCH PARSER";
			break;
		case OBJECT_TSTEMPLATE:
			tag = "ALTER TEXT SEARCH TEMPLATE";
			break;
		case OBJECT_TYPE:
			tag = "ALTER TYPE";
			break;
		case OBJECT_VIEW:
			tag = "ALTER VIEW";
			break;
		case OBJECT_MATVIEW:
			tag = "ALTER MATERIALIZED VIEW";
			break;
		case OBJECT_PUBLICATION:
			tag = "ALTER PUBLICATION";
			break;
		case OBJECT_SUBSCRIPTION:
			tag = "ALTER SUBSCRIPTION";
			break;
		case OBJECT_STATISTIC_EXT:
			tag = "ALTER STATISTICS";
			break;
		default:
			tag = "???";
			break;
	}

	return tag;
}