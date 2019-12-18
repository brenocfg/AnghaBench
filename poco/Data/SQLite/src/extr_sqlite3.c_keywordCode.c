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

/* Variables and functions */
 int* aKWCode ; 
 scalar_t__* aKWHash ; 
 int* aKWLen ; 
 scalar_t__* aKWNext ; 
 size_t* aKWOffset ; 
 int charMap (char const) ; 
 int /*<<< orphan*/  testcase (int) ; 
 char const toupper (char const) ; 
 char* zKWText ; 

__attribute__((used)) static int keywordCode(const char *z, int n, int *pType){
  int i, j;
  const char *zKW;
  if( n>=2 ){
    i = ((charMap(z[0])*4) ^ (charMap(z[n-1])*3) ^ n) % 127;
    for(i=((int)aKWHash[i])-1; i>=0; i=((int)aKWNext[i])-1){
      if( aKWLen[i]!=n ) continue;
      j = 0;
      zKW = &zKWText[aKWOffset[i]];
#ifdef SQLITE_ASCII
      while( j<n && (z[j]&~0x20)==zKW[j] ){ j++; }
#endif
#ifdef SQLITE_EBCDIC
      while( j<n && toupper(z[j])==zKW[j] ){ j++; }
#endif
      if( j<n ) continue;
      testcase( i==0 ); /* REINDEX */
      testcase( i==1 ); /* INDEXED */
      testcase( i==2 ); /* INDEX */
      testcase( i==3 ); /* DESC */
      testcase( i==4 ); /* ESCAPE */
      testcase( i==5 ); /* EACH */
      testcase( i==6 ); /* CHECK */
      testcase( i==7 ); /* KEY */
      testcase( i==8 ); /* BEFORE */
      testcase( i==9 ); /* FOREIGN */
      testcase( i==10 ); /* FOR */
      testcase( i==11 ); /* IGNORE */
      testcase( i==12 ); /* REGEXP */
      testcase( i==13 ); /* EXPLAIN */
      testcase( i==14 ); /* INSTEAD */
      testcase( i==15 ); /* ADD */
      testcase( i==16 ); /* DATABASE */
      testcase( i==17 ); /* AS */
      testcase( i==18 ); /* SELECT */
      testcase( i==19 ); /* TABLE */
      testcase( i==20 ); /* LEFT */
      testcase( i==21 ); /* THEN */
      testcase( i==22 ); /* END */
      testcase( i==23 ); /* DEFERRABLE */
      testcase( i==24 ); /* ELSE */
      testcase( i==25 ); /* EXCLUDE */
      testcase( i==26 ); /* DELETE */
      testcase( i==27 ); /* TEMPORARY */
      testcase( i==28 ); /* TEMP */
      testcase( i==29 ); /* OR */
      testcase( i==30 ); /* CONSTRAINT */
      testcase( i==31 ); /* INTERSECT */
      testcase( i==32 ); /* TIES */
      testcase( i==33 ); /* SAVEPOINT */
      testcase( i==34 ); /* INTO */
      testcase( i==35 ); /* OFFSET */
      testcase( i==36 ); /* OF */
      testcase( i==37 ); /* SET */
      testcase( i==38 ); /* TRANSACTION */
      testcase( i==39 ); /* ACTION */
      testcase( i==40 ); /* ON */
      testcase( i==41 ); /* NATURAL */
      testcase( i==42 ); /* ALTER */
      testcase( i==43 ); /* RAISE */
      testcase( i==44 ); /* EXCEPT */
      testcase( i==45 ); /* TRIGGER */
      testcase( i==46 ); /* REFERENCES */
      testcase( i==47 ); /* UNIQUE */
      testcase( i==48 ); /* QUERY */
      testcase( i==49 ); /* WITHOUT */
      testcase( i==50 ); /* WITH */
      testcase( i==51 ); /* OUTER */
      testcase( i==52 ); /* RELEASE */
      testcase( i==53 ); /* EXCLUSIVE */
      testcase( i==54 ); /* EXISTS */
      testcase( i==55 ); /* ATTACH */
      testcase( i==56 ); /* HAVING */
      testcase( i==57 ); /* GLOB */
      testcase( i==58 ); /* BEGIN */
      testcase( i==59 ); /* INNER */
      testcase( i==60 ); /* RANGE */
      testcase( i==61 ); /* BETWEEN */
      testcase( i==62 ); /* NOTHING */
      testcase( i==63 ); /* GROUPS */
      testcase( i==64 ); /* GROUP */
      testcase( i==65 ); /* CASCADE */
      testcase( i==66 ); /* ASC */
      testcase( i==67 ); /* DETACH */
      testcase( i==68 ); /* CASE */
      testcase( i==69 ); /* COLLATE */
      testcase( i==70 ); /* CREATE */
      testcase( i==71 ); /* CURRENT_DATE */
      testcase( i==72 ); /* IMMEDIATE */
      testcase( i==73 ); /* JOIN */
      testcase( i==74 ); /* INSERT */
      testcase( i==75 ); /* LIKE */
      testcase( i==76 ); /* MATCH */
      testcase( i==77 ); /* PLAN */
      testcase( i==78 ); /* ANALYZE */
      testcase( i==79 ); /* PRAGMA */
      testcase( i==80 ); /* ABORT */
      testcase( i==81 ); /* UPDATE */
      testcase( i==82 ); /* VALUES */
      testcase( i==83 ); /* VIRTUAL */
      testcase( i==84 ); /* LIMIT */
      testcase( i==85 ); /* WHEN */
      testcase( i==86 ); /* NOTNULL */
      testcase( i==87 ); /* NOT */
      testcase( i==88 ); /* NO */
      testcase( i==89 ); /* NULL */
      testcase( i==90 ); /* WHERE */
      testcase( i==91 ); /* RECURSIVE */
      testcase( i==92 ); /* AFTER */
      testcase( i==93 ); /* RENAME */
      testcase( i==94 ); /* AND */
      testcase( i==95 ); /* DEFAULT */
      testcase( i==96 ); /* AUTOINCREMENT */
      testcase( i==97 ); /* TO */
      testcase( i==98 ); /* IN */
      testcase( i==99 ); /* CAST */
      testcase( i==100 ); /* COLUMN */
      testcase( i==101 ); /* COMMIT */
      testcase( i==102 ); /* CONFLICT */
      testcase( i==103 ); /* CROSS */
      testcase( i==104 ); /* CURRENT_TIMESTAMP */
      testcase( i==105 ); /* CURRENT_TIME */
      testcase( i==106 ); /* CURRENT */
      testcase( i==107 ); /* PARTITION */
      testcase( i==108 ); /* DEFERRED */
      testcase( i==109 ); /* DISTINCT */
      testcase( i==110 ); /* IS */
      testcase( i==111 ); /* DROP */
      testcase( i==112 ); /* PRECEDING */
      testcase( i==113 ); /* FAIL */
      testcase( i==114 ); /* FILTER */
      testcase( i==115 ); /* REPLACE */
      testcase( i==116 ); /* FOLLOWING */
      testcase( i==117 ); /* FROM */
      testcase( i==118 ); /* FULL */
      testcase( i==119 ); /* IF */
      testcase( i==120 ); /* ISNULL */
      testcase( i==121 ); /* ORDER */
      testcase( i==122 ); /* RESTRICT */
      testcase( i==123 ); /* OTHERS */
      testcase( i==124 ); /* OVER */
      testcase( i==125 ); /* RIGHT */
      testcase( i==126 ); /* ROLLBACK */
      testcase( i==127 ); /* ROWS */
      testcase( i==128 ); /* ROW */
      testcase( i==129 ); /* UNBOUNDED */
      testcase( i==130 ); /* UNION */
      testcase( i==131 ); /* USING */
      testcase( i==132 ); /* VACUUM */
      testcase( i==133 ); /* VIEW */
      testcase( i==134 ); /* WINDOW */
      testcase( i==135 ); /* DO */
      testcase( i==136 ); /* BY */
      testcase( i==137 ); /* INITIALLY */
      testcase( i==138 ); /* ALL */
      testcase( i==139 ); /* PRIMARY */
      *pType = aKWCode[i];
      break;
    }
  }
  return n;
}