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
      testcase( i==0 ); /* CONSTRAINT */
      testcase( i==1 ); /* INTO */
      testcase( i==2 ); /* IN */
      testcase( i==3 ); /* TO */
      testcase( i==4 ); /* OFFSET */
      testcase( i==5 ); /* OF */
      testcase( i==6 ); /* SET */
      testcase( i==7 ); /* TABLE */
      testcase( i==8 ); /* LEFT */
      testcase( i==9 ); /* THEN */
      testcase( i==10 ); /* END */
      testcase( i==11 ); /* DESC */
      testcase( i==12 ); /* ESCAPE */
      testcase( i==13 ); /* ELSE */
      testcase( i==14 ); /* SELECT */
      testcase( i==15 ); /* TRANSACTION */
      testcase( i==16 ); /* ON */
      testcase( i==17 ); /* NATURAL */
      testcase( i==18 ); /* ALL */
      testcase( i==19 ); /* LIKE */
      testcase( i==20 ); /* KEY */
      testcase( i==21 ); /* SAVEPOINT */
      testcase( i==22 ); /* TEMPORARY */
      testcase( i==23 ); /* TEMP */
      testcase( i==24 ); /* OR */
      testcase( i==25 ); /* WITHOUT */
      testcase( i==26 ); /* WITH */
      testcase( i==27 ); /* OUTER */
      testcase( i==28 ); /* RELEASE */
      testcase( i==29 ); /* AS */
      testcase( i==30 ); /* EXCLUSIVE */
      testcase( i==31 ); /* EXISTS */
      testcase( i==32 ); /* BEGIN */
      testcase( i==33 ); /* INDEXED */
      testcase( i==34 ); /* INDEX */
      testcase( i==35 ); /* DELETE */
      testcase( i==36 ); /* BETWEEN */
      testcase( i==37 ); /* NOTHING */
      testcase( i==38 ); /* GROUP */
      testcase( i==39 ); /* UPDATE */
      testcase( i==40 ); /* CASE */
      testcase( i==41 ); /* COLLATE */
      testcase( i==42 ); /* CREATE */
      testcase( i==43 ); /* CURRENT_DATE */
      testcase( i==44 ); /* IGNORE */
      testcase( i==45 ); /* RECURSIVE */
      testcase( i==46 ); /* IMMEDIATE */
      testcase( i==47 ); /* JOIN */
      testcase( i==48 ); /* INNER */
      testcase( i==49 ); /* RANGE */
      testcase( i==50 ); /* MATCH */
      testcase( i==51 ); /* CHECK */
      testcase( i==52 ); /* VALUES */
      testcase( i==53 ); /* WHEN */
      testcase( i==54 ); /* NOTNULL */
      testcase( i==55 ); /* NOT */
      testcase( i==56 ); /* NULL */
      testcase( i==57 ); /* LIMIT */
      testcase( i==58 ); /* WHERE */
      testcase( i==59 ); /* REGEXP */
      testcase( i==60 ); /* PARTITION */
      testcase( i==61 ); /* ABORT */
      testcase( i==62 ); /* ADD */
      testcase( i==63 ); /* DEFAULT */
      testcase( i==64 ); /* ALTER */
      testcase( i==65 ); /* RENAME */
      testcase( i==66 ); /* AND */
      testcase( i==67 ); /* DEFERRED */
      testcase( i==68 ); /* DISTINCT */
      testcase( i==69 ); /* IS */
      testcase( i==70 ); /* ASC */
      testcase( i==71 ); /* COLUMN */
      testcase( i==72 ); /* COMMIT */
      testcase( i==73 ); /* CONFLICT */
      testcase( i==74 ); /* CROSS */
      testcase( i==75 ); /* CURRENT_TIMESTAMP */
      testcase( i==76 ); /* CURRENT_TIME */
      testcase( i==77 ); /* CURRENT */
      testcase( i==78 ); /* PRECEDING */
      testcase( i==79 ); /* GLOB */
      testcase( i==80 ); /* BY */
      testcase( i==81 ); /* DROP */
      testcase( i==82 ); /* PRIMARY */
      testcase( i==83 ); /* FAIL */
      testcase( i==84 ); /* FILTER */
      testcase( i==85 ); /* REPLACE */
      testcase( i==86 ); /* FOLLOWING */
      testcase( i==87 ); /* FROM */
      testcase( i==88 ); /* FULL */
      testcase( i==89 ); /* HAVING */
      testcase( i==90 ); /* IF */
      testcase( i==91 ); /* INSERT */
      testcase( i==92 ); /* ISNULL */
      testcase( i==93 ); /* ORDER */
      testcase( i==94 ); /* RIGHT */
      testcase( i==95 ); /* OVER */
      testcase( i==96 ); /* ROLLBACK */
      testcase( i==97 ); /* ROWS */
      testcase( i==98 ); /* UNBOUNDED */
      testcase( i==99 ); /* UNIQUE */
      testcase( i==100 ); /* USING */
      testcase( i==101 ); /* VIEW */
      testcase( i==102 ); /* WINDOW */
      testcase( i==103 ); /* DO */
      *pType = aKWCode[i];
      break;
    }
  }
  return n;
}