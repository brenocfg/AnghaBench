#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  tx ;
typedef  int sqlite3_int64 ;
typedef  int /*<<< orphan*/  sqlite3_context ;
typedef  int i64 ;
struct TYPE_10__ {int iJD; int validHMS; double s; int D; int M; int Y; int /*<<< orphan*/  validJD; int /*<<< orphan*/  validTZ; int /*<<< orphan*/  m; int /*<<< orphan*/  h; } ;
typedef  TYPE_1__ DateTime ;

/* Variables and functions */
 int ArraySize (char*) ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_UTF8 ; 
 int /*<<< orphan*/  clearYMD_HMS_TZ (TYPE_1__*) ; 
 int /*<<< orphan*/  computeJD (TYPE_1__*) ; 
 int /*<<< orphan*/  computeYMD (TYPE_1__*) ; 
 int /*<<< orphan*/  computeYMD_HMS (TYPE_1__*) ; 
 int localtimeOffset (TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  parseHhMmSs (char const*,TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3AtoF (char*,double*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3Isdigit (char const) ; 
 int /*<<< orphan*/  sqlite3Isspace (char) ; 
 int sqlite3Strlen30 (char*) ; 
 scalar_t__* sqlite3UpperToLower ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int parseModifier(sqlite3_context *pCtx, const char *zMod, DateTime *p){
  int rc = 1;
  int n;
  double r;
  char *z, zBuf[30];
  z = zBuf;
  for(n=0; n<ArraySize(zBuf)-1 && zMod[n]; n++){
    z[n] = (char)sqlite3UpperToLower[(u8)zMod[n]];
  }
  z[n] = 0;
  switch( z[0] ){
#ifndef SQLITE_OMIT_LOCALTIME
    case 'l': {
      /*    localtime
      **
      ** Assuming the current time value is UTC (a.k.a. GMT), shift it to
      ** show local time.
      */
      if( strcmp(z, "localtime")==0 ){
        computeJD(p);
        p->iJD += localtimeOffset(p, pCtx, &rc);
        clearYMD_HMS_TZ(p);
      }
      break;
    }
#endif
    case 'u': {
      /*
      **    unixepoch
      **
      ** Treat the current value of p->iJD as the number of
      ** seconds since 1970.  Convert to a real julian day number.
      */
      if( strcmp(z, "unixepoch")==0 && p->validJD ){
        p->iJD = (p->iJD + 43200)/86400 + 21086676*(i64)10000000;
        clearYMD_HMS_TZ(p);
        rc = 0;
      }
#ifndef SQLITE_OMIT_LOCALTIME
      else if( strcmp(z, "utc")==0 ){
        sqlite3_int64 c1;
        computeJD(p);
        c1 = localtimeOffset(p, pCtx, &rc);
        if( rc==SQLITE_OK ){
          p->iJD -= c1;
          clearYMD_HMS_TZ(p);
          p->iJD += c1 - localtimeOffset(p, pCtx, &rc);
        }
      }
#endif
      break;
    }
    case 'w': {
      /*
      **    weekday N
      **
      ** Move the date to the same time on the next occurrence of
      ** weekday N where 0==Sunday, 1==Monday, and so forth.  If the
      ** date is already on the appropriate weekday, this is a no-op.
      */
      if( strncmp(z, "weekday ", 8)==0
               && sqlite3AtoF(&z[8], &r, sqlite3Strlen30(&z[8]), SQLITE_UTF8)
               && (n=(int)r)==r && n>=0 && r<7 ){
        sqlite3_int64 Z;
        computeYMD_HMS(p);
        p->validTZ = 0;
        p->validJD = 0;
        computeJD(p);
        Z = ((p->iJD + 129600000)/86400000) % 7;
        if( Z>n ) Z -= 7;
        p->iJD += (n - Z)*86400000;
        clearYMD_HMS_TZ(p);
        rc = 0;
      }
      break;
    }
    case 's': {
      /*
      **    start of TTTTT
      **
      ** Move the date backwards to the beginning of the current day,
      ** or month or year.
      */
      if( strncmp(z, "start of ", 9)!=0 ) break;
      z += 9;
      computeYMD(p);
      p->validHMS = 1;
      p->h = p->m = 0;
      p->s = 0.0;
      p->validTZ = 0;
      p->validJD = 0;
      if( strcmp(z,"month")==0 ){
        p->D = 1;
        rc = 0;
      }else if( strcmp(z,"year")==0 ){
        computeYMD(p);
        p->M = 1;
        p->D = 1;
        rc = 0;
      }else if( strcmp(z,"day")==0 ){
        rc = 0;
      }
      break;
    }
    case '+':
    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
      double rRounder;
      for(n=1; z[n] && z[n]!=':' && !sqlite3Isspace(z[n]); n++){}
      if( !sqlite3AtoF(z, &r, n, SQLITE_UTF8) ){
        rc = 1;
        break;
      }
      if( z[n]==':' ){
        /* A modifier of the form (+|-)HH:MM:SS.FFF adds (or subtracts) the
        ** specified number of hours, minutes, seconds, and fractional seconds
        ** to the time.  The ".FFF" may be omitted.  The ":SS.FFF" may be
        ** omitted.
        */
        const char *z2 = z;
        DateTime tx;
        sqlite3_int64 day;
        if( !sqlite3Isdigit(*z2) ) z2++;
        memset(&tx, 0, sizeof(tx));
        if( parseHhMmSs(z2, &tx) ) break;
        computeJD(&tx);
        tx.iJD -= 43200000;
        day = tx.iJD/86400000;
        tx.iJD -= day*86400000;
        if( z[0]=='-' ) tx.iJD = -tx.iJD;
        computeJD(p);
        clearYMD_HMS_TZ(p);
        p->iJD += tx.iJD;
        rc = 0;
        break;
      }
      z += n;
      while( sqlite3Isspace(*z) ) z++;
      n = sqlite3Strlen30(z);
      if( n>10 || n<3 ) break;
      if( z[n-1]=='s' ){ z[n-1] = 0; n--; }
      computeJD(p);
      rc = 0;
      rRounder = r<0 ? -0.5 : +0.5;
      if( n==3 && strcmp(z,"day")==0 ){
        p->iJD += (sqlite3_int64)(r*86400000.0 + rRounder);
      }else if( n==4 && strcmp(z,"hour")==0 ){
        p->iJD += (sqlite3_int64)(r*(86400000.0/24.0) + rRounder);
      }else if( n==6 && strcmp(z,"minute")==0 ){
        p->iJD += (sqlite3_int64)(r*(86400000.0/(24.0*60.0)) + rRounder);
      }else if( n==6 && strcmp(z,"second")==0 ){
        p->iJD += (sqlite3_int64)(r*(86400000.0/(24.0*60.0*60.0)) + rRounder);
      }else if( n==5 && strcmp(z,"month")==0 ){
        int x, y;
        computeYMD_HMS(p);
        p->M += (int)r;
        x = p->M>0 ? (p->M-1)/12 : (p->M-12)/12;
        p->Y += x;
        p->M -= x*12;
        p->validJD = 0;
        computeJD(p);
        y = (int)r;
        if( y!=r ){
          p->iJD += (sqlite3_int64)((r - y)*30.0*86400000.0 + rRounder);
        }
      }else if( n==4 && strcmp(z,"year")==0 ){
        int y = (int)r;
        computeYMD_HMS(p);
        p->Y += y;
        p->validJD = 0;
        computeJD(p);
        if( y!=r ){
          p->iJD += (sqlite3_int64)((r - y)*365.0*86400000.0 + rRounder);
        }
      }else{
        rc = 1;
      }
      clearYMD_HMS_TZ(p);
      break;
    }
    default: {
      break;
    }
  }
  return rc;
}